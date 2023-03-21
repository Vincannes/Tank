import os
import sys
import logging
import posixpath
import ntpath
import six_import as six
from yaml_cache import YamlCache
import contants_import as constants

# with open(r"D:\Desk\python\Tank\config\template.yml", "r") as stream:
#     _templates = yaml.safe_load(stream)

yaml_cache = YamlCache()

log = logging.getLogger(__name__)


class PipelineConfiguration(object):
    """
    Represents a pipeline configuration in Tank.

    Use the factory methods in pipelineconfig_factory
    to construct this object, do not create directly via the constructor.
    """

    def __init__(self, pipeline_configuration_path, descriptor=None):
        """
        Constructor. Do not call this directly, use the factory methods
        in pipelineconfig_factory.

        NOTE ABOUT SYMLINKS!

        The pipeline_configuration_path is always populated by the paths
        that were registered in shotgun, regardless of how the symlink setup
        is handled on the OS level.

        :param str pipeline_configuration_path: Path to the pipeline configuration on disk.
        :param descriptor: Descriptor that was used to create this pipeline configuration.
            Defaults to ``None`` for backwards compatibility with Bootstrapper that only
            pass down one argument. Also this argument was passed down by cores from
            v0.18.72 to 0.18.94. The descriptor is now read from the disk inside
            pipeline_configuration.yml.
        :type descriptor: :class:`sgtk.descriptor.ConfigDescriptor`
        """
        self._pc_root = pipeline_configuration_path
        self._project_name = "Test"
        config_folder = os.path.join(self._pc_root, "config")
        self._storage_roots = StorageRoot().from_config(config_folder)

    def get_all_platform_data_roots(self):
        r"""
        Similar to get_data_roots but instead of returning project data roots
        for a single operating system, the data roots for all operating systems
        are returned.

        The return structure is a nested dictionary structure, for example::

            {
                "primary": {
                    "win32": "z:\studio\my_project",
                    "linux2": "/studio/my_project",
                    "darwin": "/studio/my_project"
                },
                "textures": {
                    "win32": "z:\textures\my_project",
                    "linux2": None,
                    "darwin": "/textures/my_project"
                },
            }

        The operating system keys are returned on sys.platform-style notation.
        If a data root has not been defined on a particular platform, None is
        returned (see example above).

        :returns: dictionary of dictionaries. See above.
        """

        project_roots_lookup = {}
        print(self._storage_roots.as_shotgun_paths.items())
        for root_name, sg_path in self._storage_roots.as_shotgun_paths.items():
            # join the project name to the storage ShotgunPath
            project_root = sg_path.join(self._project_name)

            # break out the ShotgunPath object in sys.platform style dict
            project_roots_lookup[root_name] = project_root.as_system_dict()

        return project_roots_lookup

    def _get_templates_config_location(self):
        """
        Returns the path to the configuration's template file.
        """
        return os.path.join(
            "D:\Desk\python\Tank\config",
            constants.CONTENT_TEMPLATES_FILE,
        )

    def get_templates_config(self):
        """
        Returns the templates configuration as an object
        """
        templates_file = self._get_templates_config_location()

        try:
            data = (
                    yaml_cache.get(templates_file, deepcopy_data=False) or {}
            )
            data = process_includes(templates_file, data)
        except ValueError:
            data = dict()

        return data


class ShotgunPath(object):

    @staticmethod
    def get_file_name_from_template(template, platform=sys.platform):
        """
        Returns the complete file name for the current platform based on
        file name template passed in.

        :param str template: Template for a file name with a ``%s`` to indicate
            where the platform name should be inserted.

        :returns: Path with the OS name substituted in.
        """
        os_name = "Windows"
        return template % os_name

    @classmethod
    def from_shotgun_dict(cls, sg_dict):
        """
        Creates a path from data contained in a std shotgun data dict,
        containing the paths windows_path, mac_path and linux_path

        :param sg_dict: Shotgun query resultset with possible keys
                        windows_path, mac_path and linux_path.
        :return: :class:`ShotgunPath` instance
        """
        windows_path = sg_dict.get("windows_path")
        linux_path = sg_dict.get("linux_path")
        macosx_path = sg_dict.get("mac_path")
        return cls(windows_path, linux_path, macosx_path)

    @classmethod
    def from_current_os_path(cls, path):
        """
        Creates a path object for a path on the current platform only.

        :param path: Path on the current os platform.
        :return: :class:`ShotgunPath` instance
        """
        linux_path = None
        macosx_path = None
        windows_path = path

        return cls(windows_path, linux_path, macosx_path)

    @classmethod
    def normalize(cls, path):
        """
        Convenience method that normalizes the given path
        by running it through the :class:`ShotgunPath` normalization
        logic. ``ShotgunPath.normalize(path)`` is equivalent
        to executing ``ShotgunPath.from_current_os_path(path).current_os``.

        Normalization include checking that separators are matching the
        current operating system, removal of trailing separators
        and removal of double separators. This is done automatically
        for all :class:`ShotgunPath`, but sometimes it is useful
        to just perform the normalization quickly on a local path.

        :param str path: Local operating system path to normalize
        :return: Normalized path string.
        """
        return cls.from_current_os_path(path).current_os

    def __init__(self, windows_path=None, linux_path=None, macosx_path=None):
        """
        :param windows_path: Path on windows to associate with this path object
        :param linux_path: Path on linux to associate with this path object
        :param macosx_path: Path on macosx to associate with this path object
        """
        self._windows_path = self._sanitize_path(windows_path, "\\")
        self._linux_path = self._sanitize_path(linux_path, "/")
        self._macosx_path = self._sanitize_path(macosx_path, "/")
        self.current_os = self._windows_path

    def _sanitize_path(self, path, separator):
        r"""
        Multi-platform sanitize and clean up of paths.

        The following modifications will be carried out:

        None returns None

        Trailing slashes are removed:
        1. /foo/bar      - unchanged
        2. /foo/bar/     - /foo/bar
        3. z:/foo/       - z:\foo
        4. z:/           - z:\
        5. z:\           - z:\
        6. \\foo\bar\    - \\foo\bar

        Double slashes are removed:
        1. //foo//bar    - /foo/bar
        2. \\foo\\bar    - \\foo\bar

        Leading and trailing spaces are removed:
        1. "   Z:\foo  " - "Z:\foo"

        :param path: the path to clean up
        :param separator: the os.sep to adjust the path for. / on nix, \ on win.
        :returns: cleaned up path
        """
        if path is None:
            return None

        # ensure there is no white space around the path
        path = path.strip()

        # get rid of any slashes at the end
        # after this step, path value will be "/foo/bar", "c:" or "\\hello"
        path = path.rstrip("/\\")

        # add slash for drive letters: c: --> c:/
        if len(path) == 2 and path.endswith(":"):
            path += "/"

        # and convert to the right separators
        # after this we have a path with the correct slashes and no end slash
        local_path = path.replace("\\", separator).replace("/", separator)

        # now weed out any duplicated slashes. iterate until done
        while True:
            new_path = local_path.replace("//", "/")
            if new_path == local_path:
                break
            else:
                local_path = new_path

        # for windows, remove duplicated backslashes, except if they are
        # at the beginning of the path
        while True:
            new_path = local_path[0] + local_path[1:].replace("\\\\", "\\")
            if new_path == local_path:
                break
            else:
                local_path = new_path

        return local_path


class StorageRoot(object):
    LEGACY_DEFAULT_STORAGE_NAME = "primary"

    # the relative path where storage roots are defined in a configuration
    STORAGE_ROOTS_FILE_PATH = os.path.join("core", "roots.yml")

    # sys.platform-specific path keys as expected in the root definitions
    PLATFORM_KEYS = ["mac_path", "linux_path", "windows_path"]

    @classmethod
    def from_config(cls, config_folder):
        """
        Constructs a StorageRoots object from the supplied config folder.

        The supplied config folder may or may not define required storage roots,
        but the method will return a ``StorageRoots`` instance anyway.

        :param config_folder: The path to a config folder
        :returns: A ``StorageRoots`` object instance
        """

        log.debug("Creating StorageRoots instance from config: %s" % (config_folder,))
        storage_roots = cls()
        storage_roots._init_from_config(config_folder)
        log.debug("Created: %s" % (storage_roots,))

        return storage_roots

    def __init__(self):
        # the path to the config folder
        self._config_root_folder = None

        # the path to the roots file
        self._storage_roots_file = None

        # the underlying metadata for the required storage roots
        self._storage_roots_metadata = {}

        # a lookup of storage root names to shotgun paths
        self._shotgun_paths_lookup = {}

        # the default storage name as determined when parsing the metadata
        self._default_storage_name = None

    @property
    def required_roots(self):
        """
        A list of all required storage root names (``str``) by this
        configuration.
        """
        return list(self._storage_roots_metadata.keys())

    def __iter__(self):
        """
        Allows iteration over each defined root name and corresponding metadata.

        Yields root names and corresponding metadata upon iteration.
        """
        for root_name, root_info in self._storage_roots_metadata.items():
            yield root_name, root_info

    def __repr__(self):
        """
        Returns a string representation of the object.
        """
        return "<StorageRoots folder:'%s', roots:'%s'>" % (
            self._config_root_folder,
            ",".join(self.required_roots),
        )


    def _init_from_config(self, config_folder):
        """
        Initialize the internal object data with the required storage roots
        defined under the supplied config folder.

        :param config_folder: The path to a configuration
        """

        log.debug(
            "Initializing storage roots object. "
            "Supplied config folder: %s" % (config_folder,)
        )

        # ---- set some basic data for the object

        # the supplied roots' folder, just in case
        self._config_root_folder = config_folder

        # the full path to the roots file for debugging/messages
        self._storage_roots_file = os.path.join(
            self._config_root_folder, self.STORAGE_ROOTS_FILE_PATH
        )

        log.debug(
            "Storage roots file defined in the config: %s" % (self._storage_roots_file,)
        )

        # load the roots file and store the metadata
        if os.path.exists(self._storage_roots_file):
            roots_metadata = _get_storage_roots_metadata(self._storage_roots_file)
        else:
            # file does not exist. we will initialize with an empty dict
            roots_metadata = {}

        self._process_metadata(roots_metadata)

    @property
    def as_shotgun_paths(self):
        """
        A dictionary mapping of storage root names to ShotgunPath objects

        :returns: A dictionary structure with an entry for each storage defined.
            The value of each is a ShotgunPath object for the storage's path
            on disk.

        Example return dictionary::

            {
                "primary"  : <ShotgunPath>,
                "textures" : <ShotgunPath>
            }
        """
        return self._shotgun_paths_lookup

    def _process_metadata(self, roots_metadata):
        """
        Processes the supplied roots metadata and populates the internal object
        data structures. This includes storing easy access to the default root
        and other commonly accessed information.

        :param dict roots_metadata: A dictonary of metadata to use to populate
            the object. See the ``from_metadata`` class method for more info.
        """

        log.debug("Storage roots metadata: %s" % (roots_metadata,))

        # store it on the object
        self._storage_roots_metadata = roots_metadata

        # ---- store information about the roots for easy access

        log.debug("Processing required storages defined by the config...")

        # iterate over each storage root required by the configuration. try to
        # identify the default root.
        for root_name, root_info in self:

            log.debug("Processing storage: %s - %s" % (root_name, root_info))

            # store a shotgun path for each root definition. sanitize path data
            # by passing it through the ShotgunPath object. if the configuration
            # has not been installed, these paths may be None.
            self._shotgun_paths_lookup[root_name] = ShotgunPath.from_shotgun_dict(
                root_info
            )

            # check to see if this root is marked as the default
            if root_info.get("default", False):
                log.debug(
                    "Storage root %s explicitly marked as the default." % (root_name,)
                )
                self._default_storage_name = root_name

        # no default storage root defined explicitly. try to identify one if
        # there are storage roots defined
        if self.required_roots and not self._default_storage_name:

            log.debug("No default storage explicitly defined...")

            # if there is only one, then that is the default
            if len(roots_metadata) == 1:
                sole_storage_root = list(roots_metadata.keys())[0]
                log.debug(
                    "Storage %s identified as the default root because it is "
                    "the only root required by the configuration" % (sole_storage_root,)
                )
                self._default_storage_name = sole_storage_root
            elif self.LEGACY_DEFAULT_STORAGE_NAME in roots_metadata:
                # legacy primary storage name defined. that is the default
                log.debug(
                    "Storage %s identified as the default root because it "
                    "matches the legacy default root name."
                    % (self.LEGACY_DEFAULT_STORAGE_NAME,)
                )
                self._default_storage_name = self.LEGACY_DEFAULT_STORAGE_NAME
            else:
                # default storage will be None
                log.warning(
                    "Unable to identify a default storage root in the config's "
                    "required storages."
                )


def _get_storage_roots_metadata(storage_roots_file):
    """
    Parse the supplied storage roots file

    :param storage_roots_file: Path to the roots file.
    :return: The parsed metadata as a dictionary.
    """

    log.debug("Reading storage roots file form disk: %s" % (storage_roots_file,))

    try:
        # keep a handle on the raw metadata read from the roots file
        roots_metadata = (
                yaml_cache.get(storage_roots_file, deepcopy_data=False) or {}
        )  # if file is empty, initialize with empty dict
    except Exception as e:
        raise ValueError(
            "Looks like the roots file is corrupt. "
            "Please contact support! "
            "File: '%s'. "
            "Error: %s" % (storage_roots_file, e)
        )

    log.debug("Read metadata: %s" % (roots_metadata,))

    return roots_metadata


def process_includes(file_name, data):
    """
    Processes includes for the main templates file. Will look for
    any include data structures and transform them into real data.

    Algorithm (recursive):

    1. first load in include data into keys, strings, path sections.
       if there are multiple files, they are loaded in order.
    2. now, on top of this, load in this file's keys, strings and path defs
    3. lastly, process all @refs in the paths section

    """
    # first recursively load all template data from includes
    resolved_includes_data = _process_template_includes_r(file_name, data)

    # Now recursively process any @resolves.
    # these are of the following form:
    #   foo: bar
    #   ttt: @foo/something
    # You can only use these in the paths and strings sections.
    #
    # @ can be used anywhere in the template definition.  @ should
    # be used to escape itself if required.  e.g.:
    #   foo: bar
    #   ttt: @foo/something/@@/_@foo_
    # Would result in:
    #   bar/something/@/_bar_
    template_paths = resolved_includes_data[constants.TEMPLATE_PATH_SECTION]
    template_strings = resolved_includes_data[constants.TEMPLATE_STRING_SECTION]

    # process the template paths section:
    for template_name, template_definition in template_paths.items():
        _resolve_template_r(
            template_paths, template_strings, template_name, template_definition, "path"
        )

    # and process the strings section:
    for template_name, template_definition in template_strings.items():
        _resolve_template_r(
            template_paths,
            template_strings,
            template_name,
            template_definition,
            "string",
        )

    # finally, resolve escaped @'s in template definitions:
    for templates in [template_paths, template_strings]:
        for template_name, template_definition in templates.items():
            # find the template string from the definition:
            template_str = None
            complex_syntax = False
            if isinstance(template_definition, dict):
                template_str = template_definition.get("definition")
                complex_syntax = True
            elif isinstance(template_definition, six.string_types):
                template_str = template_definition
            if not template_str:
                raise ValueError(
                    "Invalid template configuration for '%s' - "
                    "it looks like the definition is missing!" % (template_name)
                )

            # resolve escaped @'s
            resolved_template_str = template_str.replace("@@", "@")
            if resolved_template_str == template_str:
                continue

            # set the value back again:
            if complex_syntax:
                templates[template_name]["definition"] = resolved_template_str
            else:
                templates[template_name] = resolved_template_str

    return resolved_includes_data


def _process_template_includes_r(file_name, data):
    """
    Recursively add template include files.

    For each of the sections keys, strings, path, populate entries based on
    include files.
    """

    # return data
    output_data = {}
    # add items for keys, paths, strings etc
    for ts in constants.TEMPLATE_SECTIONS:
        output_data[ts] = {}

    if data is None:
        return output_data

    # process includes
    included_paths = _get_includes(file_name, data)

    for included_path in included_paths:
        included_data = (
            yaml_cache.get(included_path, deepcopy_data=False) or dict()
        )

        # before doing any type of processing, allow the included data to be resolved.
        included_data = _process_template_includes_r(included_path, included_data)

        # add the included data's different sections
        for ts in constants.TEMPLATE_SECTIONS:
            if ts in included_data:
                output_data[ts].update(included_data[ts])

    # now all include data has been added into the data structure.
    # now add the template data itself
    for ts in constants.TEMPLATE_SECTIONS:
        if ts in data:
            output_data[ts].update(data[ts])

    return output_data


def _resolve_template_r(
    template_paths,
    template_strings,
    template_name,
    template_definition,
    template_type,
    template_chain=None,
):
    """
    Recursively resolve path templates so that they are fully expanded.
    """

    # check we haven't searched this template before and keep
    # track of the ones we have visited
    template_key = (template_name, template_type)
    visited_templates = list(template_chain or [])
    if template_key in visited_templates:
        raise ValueError(
            "A cyclic %s template was found - '%s' references itself (%s)"
            % (
                template_type,
                template_name,
                " -> ".join(
                    [
                        name
                        for name, _ in visited_templates[
                            visited_templates.index(template_key) :
                        ]
                    ]
                    + [template_name]
                ),
            )
        )
    visited_templates.append(template_key)

    # find the template string from the definition:
    template_str = None
    complex_syntax = False
    if isinstance(template_definition, dict):
        template_str = template_definition.get("definition")
        complex_syntax = True
    elif isinstance(template_definition, six.string_types):
        template_str = template_definition
    if not template_str:
        raise ValueError(
            "Invalid template configuration for '%s' - it looks like the "
            "definition is missing!" % (template_name)
        )

    # look for @ specified in template definition.  This can be escaped by
    # using @@ so split out escaped @'s first:
    template_str_parts = template_str.split("@@")
    resolved_template_str_parts = []
    for part in template_str_parts:

        # split to find seperate @ include parts:
        ref_parts = part.split("@")
        resolved_ref_parts = ref_parts[:1]
        for ref_part in ref_parts[1:]:

            if not ref_part:
                # this would have been an @ so ignore!
                continue

            # find a template that matches the start of the template string:
            ref_template = _find_matching_ref_template(
                template_paths, template_strings, ref_part
            )
            if not ref_template:
                raise ValueError(
                    "Failed to resolve template reference from '@%s' defined by "
                    "the %s template '%s'" % (ref_part, template_type, template_name)
                )

            # resolve the referenced template:
            ref_template_name, ref_template_definition, ref_template_type = ref_template
            resolved_ref_str = _resolve_template_r(
                template_paths,
                template_strings,
                ref_template_name,
                ref_template_definition,
                ref_template_type,
                visited_templates,
            )
            resolved_ref_str = "%s%s" % (
                resolved_ref_str,
                ref_part[len(ref_template_name) :],
            )

            resolved_ref_parts.append(resolved_ref_str)

        # rejoin resolved parts:
        resolved_template_str_parts.append("".join(resolved_ref_parts))

    # re-join resolved parts with escaped @:
    resolved_template_str = "@@".join(resolved_template_str_parts)

    # put the value back:
    templates = {"path": template_paths, "string": template_strings}[template_type]
    if complex_syntax:
        templates[template_name]["definition"] = resolved_template_str
    else:
        templates[template_name] = resolved_template_str

    return resolved_template_str


def _find_matching_ref_template(template_paths, template_strings, ref_string):
    """
    Find a template whose name matches a portion of ref_string.  This
    will find the longest/best match and will look at both path and string
    templates
    """
    matching_templates = []

    # find all templates that match the start of the ref string:
    for templates, template_type in [
        (template_paths, "path"),
        (template_strings, "string"),
    ]:
        for name, definition in templates.items():
            if ref_string.startswith(name):
                matching_templates.append((name, definition, template_type))

    # if there are more than one then choose the one with the longest
    # name/longest match:
    best_match = None
    best_match_len = 0
    for name, definition, template_type in matching_templates:
        name_len = len(name)
        if name_len > best_match_len:
            best_match_len = name_len
            best_match = (name, definition, template_type)

    return best_match


def _get_includes(file_name, data):
    """
    Parse the includes section and return a list of valid paths

    :param str file_name: Name of the file to parse.
    :param aray or str data: Include path or array of include paths to evaluate.
    """
    includes = []

    resolved_includes = list()

    if constants.SINGLE_INCLUDE_SECTION in data:
        # single include section
        includes.append(data[constants.SINGLE_INCLUDE_SECTION])

    if constants.MULTI_INCLUDE_SECTION in data:
        # multi include section
        includes.extend(data[constants.MULTI_INCLUDE_SECTION])

    for include in includes:
        resolved = resolve_include(file_name, include)
        if resolved and resolved not in resolved_includes:
            resolved_includes.append(resolved)

    return resolved_includes


def resolve_include(file_name, include):
    """
    Resolve an include.

    If the path has a ~ or an environment variable, it will be resolved first.

    If the path is relative, it will be considered relative to the file that
    included it and it will be considered for any OS.

    If the path is absolute, it will only be considered to be a valid include if
    it is an absolute path for the current platform.

    Finally, the path will be sanitized to remove any extraneous slashes or slashes
    in the wrong direction.

    :param str file_name: Name of the file containing the include.
    :param str include: Include to resolve.

    :returns str: An absolute path to the resolved include or None if the file wasn't
        specified for the current platform.

    :raises TankError: Raised when the path doesn't exist.
    """
    # First resolve all environment variables and ~
    path = os.path.expanduser(os.path.expandvars(include))

    # If the path is not absolute, make it so!
    value = posixpath.isabs(path) or ntpath.isabs(path)
    if not value:
        # Append it to the current file's directory.
        path = os.path.join(os.path.dirname(file_name), path)
    # We have an absolute path, so check if it is meant for this platform.
    elif not _is_current_platform_abspath(path):
        # It wasn't meant for this platform, return nothing.
        return None

    # ShotgunPath cleans up paths so that slashes are all
    # in the same direction and no doubles exist.
    path = ShotgunPath.normalize(path)

    # make sure that the paths all exist
    if not os.path.exists(path):
        raise ValueError(
            "Include resolve error in '%s': '%s' resolved to '%s' which does not exist!"
            % (file_name, include, path)
        )

    return path


def _is_current_platform_abspath(path):
    """
    Check if the path is an obsolute path for the current platform.

    :param str path: Path to validate.

    :returns bool: True if absolute for this platform, False otherwise.
    """
    return ntpath.isabs(path) and not posixpath.isabs(path)
