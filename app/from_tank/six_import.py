import sys
import types


class _LazyModule(types.ModuleType):

    def __init__(self, name):
        super(_LazyModule, self).__init__(name)
        self.__doc__ = self.__class__.__doc__

    def __dir__(self):
        attrs = ["__doc__", "__name__"]
        attrs += [attr.name for attr in self._moved_attributes]
        return attrs

    # Subclasses should override this
    _moved_attributes = []

class _MovedItems(_LazyModule):

    """Lazy loading of moved objects"""
    __path__ = []  # mark as package



def normalize_platform(platform, python2=True):
    """
    Normalize the return of sys.platform between Python 2 and 3.

    On Python 2 on linux hosts, sys.platform was 'linux' appended with the
    current kernel version that Python was built on.  In Python3, this was
    changed and sys.platform now returns 'linux' regardless of the kernel version.
    See https://bugs.python.org/issue12326
    This function will normalize platform strings to always conform to Python2 or
    Python3 behavior.

    :param str platform: The platform string to normalize
    :param bool python2: The python version behavior to target.  If True, a
        Python2-style platform string will be returned (i.e. 'linux2'), otherwise
        the modern 'linux' platform string will be returned.

    :returns: The normalized platform string.
    :rtype: str
    """
    if python2:
        return "linux2" if platform.startswith("linux") else platform
    return "linux" if platform.startswith("linux") else platform

moves = _MovedItems(__name__ + ".moves")
PLATEFORM = normalize_platform(sys.platform)
string_types = str