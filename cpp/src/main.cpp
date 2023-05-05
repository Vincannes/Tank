#include <map>
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip> // Pour setw

#include "template_obj.h"
#include "tank_obj.h"



int main() {

	std::map<std::string, std::string> fields;
	fields["dir"] = "test";
	fields["Shot"] = "sh_030";
	fields["Task"] = "cmp";
	fields["version"] = "1";
	fields["Sequence"] = "sh";
	fields["render_source"] = "nk";
	// fields["SEQ"] = "####";
	fields["write_node"] = "out";
	fields["variant"] = "base";
	fields["colorspace"] = "linear";
	fields["name"] = "sh_030";
	fields["ext_render_nuke"] = "exr";

	std::string keysOLD  = "{'Root' : {'type': 'str'}, 'dir' : {'type': 'str'}, 'Shot' : {'type': 'str', 'choices':['sh_030', 'sh_040']}, 'version' : {'alias':'version', 'type': 'int', 'default': '1', 'format_spec: '03'}, 'Task' : {'type': 'str', 'default': 'aa'}";
	std::string pathsOLD = "{'rootDir': 'D:\\Desk\\python\\Tank\\tests\\project', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}', 'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', 'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}";
	
	// std::string keys = "{'ext_render_nuke': {'type':'str', 'default':'exr', 'choices':['jpg', 'exr']}, 'SEQ': {'type':'str', 'default':'####'}, 'colorspace': {'type': 'str', 'type': 'str'}, 'Shot': {'type': 'str'}, 'version': {'type': 'int', 'default': '1'}, 'variant': {'type': 'str', 'default': 'base'},"\
	// 				   " 'render_source': {'type': 'str', 'default':'base'}, 'write_node': {'type': 'str'}, 'Sequence': {'type': 'str'}, 'Task' : {'type': 'str', 'default': 'roto'}, 'name': {'type':'str'}}";
	std::string keys = "{'Sequence': {'type': 'str', 'filter_by': '^(?!_InvalidName_)\\w+$'}, 'Shot': {'type': 'str', 'filter_by': '^(?!_InvalidName_)\\w+$'}, 'Step': {'type': 'str'}, 'sg_asset_type': {'type': 'str'}, 'Asset': {'type': 'str', 'filter_by': '^(?!_InvalidName_)\\w+$'}, 'name': {'type': 'str', 'filter_by': '\\w+'}, 'iteration': {'type': 'int'}, 'version': {'type': 'int', 'format_spec': '03'}, 'version_four': {'type': 'int', 'format_spec': '04', 'alias': 'version'}, 'special_version': {'type': 'str', 'filter_by': '^(last|valid)$'}, 'timestamp': {'type': 'str'}, 'width': {'type': 'int'}, 'height': {'type': 'int'}, 'shot_client_review_name': {'type': 'str'}, 'playlist_name': {'type': 'str'}, 'path_additional': {'type': 'str'}, 'project_resolution': {'type': 'str', 'filter_by': '^[^\\.]+$'}, 'slate_frame': {'type': 'sequence', 'format_spec': '04'}, 'delivery_image_type': {'type': 'str'}, 'client_step': {'type': 'str'}, 'delivery_quicktime_suffix': {'type': 'str'}, 'cut_name': {'type': 'str'}, 'cut_revision': {'type': 'int'}, 'tool': {'type': 'str'}, 'output': {'alias': 'nuke.output', 'type': 'str', 'filter_by': 'alphanumeric'}, 'SEQ': {'type': 'sequence', 'format_spec': '04'}, 'HSEQ': {'type': 'sequence', 'format_spec': '04', 'default': 'FORMAT: $F'}, 'eye': {'type': 'str', 'choices': ['left', 'right']}, 'houdini.node': {'alias': 'node', 'type': 'str'}, 'golaem_node': {'type': 'str'}, 'aov_name': {'type': 'str'}, 'YYYY': {'type': 'int', 'format_spec': '04'}, 'MM': {'type': 'int', 'format_spec': '02'}, 'DD': {'type': 'int', 'format_spec': '02', 'alias': 'DD'}, 'project': {'type': 'str'}, 'UDIM': {'type': 'sequence', 'default': '<UDIM>'}, 'mari.channel': {'type': 'str', 'alias': 'channel'}, 'mari.layer': {'type': 'str', 'alias': 'layer'}, 'mari.project_name': {'type': 'str', 'alias': 'name'}, 'layer': {'type': 'str'}, 'asset_name': {'type': 'str', 'shotgun_entity_type': 'Asset', 'shotgun_field_name': 'code'}, 'task_name': {'type': 'str', 'shotgun_entity_type': 'Task', 'shotgun_field_name': 'content'}, 'distribution_index': {'type': 'str'}, 'distribution_type': {'type': 'str'}, 'Task': {'type': 'str'}, 'render_iteration': {'type': 'int', 'format_spec': '03'}, 'variant': {'type': 'str', 'default': 'base'}, 'extension': {'type': 'str', 'filter_by': '^[a-zA-Z0-9]{1,5}$'}, 'render_layer': {'type': 'str', 'filter_by': '^[^.]+$'}, 'render_aov': {'type': 'str'}, 'clarisse_image': {'type': 'str'}, 'clarisse_layer': {'type': 'str'}, 'image_ext': {'type': 'str', 'choices': ['jpg', 'png', 'exr']}, 'ext_render_nuke': {'choices': ['jpg', 'dpx', 'png', 'exr', 'tiff', 'mov', 'tga'], 'type': 'str'}, 'ext_render_flame': {'choices': ['jpg', 'dpx', 'exr', 'tiff', 'tga'], 'type': 'str'}, 'ext_cache_houdini': {'choices': ['abc', 'ass', 'ifd', 'bhclassic', 'bgeo', 'bgeo.sc', 'obj', 'vdb'], 'type': 'str'}, 'ext_proxy': {'type': 'str', 'choices': ['jpg', 'png', 'exr'], 'default': 'jpg'}, 'ext_scene_photoshop': {'choices': ['psd', 'psb'], 'type': 'str'}, 'cache_type_houdini': {'type': 'str', 'choices': ['abc', 'ass', 'ifd', 'bhclassic', 'bgeo', 'obj', 'vdb']}, 'ext_render_clarisse': {'choices': ['jpg', 'bmp', 'png', 'exr', 'tiff', 'tga'], 'type': 'str'}, 'ext_render_afterfx': {'choices': ['jpg', 'png', 'exr', 'tiff'], 'type': 'str'}, 'ext_render_blender': {'choices': ['jpg', 'png', 'exr', 'tiff'], 'type': 'str'}, 'ext_render_c4d': {'choices': ['exr', 'tiff', 'jpg', 'png'], 'type': 'str'}, 'ext_cache_maya': {'choices': ['abc', 'ass', 'fur', 'vdb'], 'type': 'str'}, 'render_source': {'type': 'str', 'choices': ['mtoa', 'nk', 'nkelem', 'nkcache', 'nkmatte', 'ps', 'c4dtoa']}, 'flame_render_source': {'type': 'str', 'choices': ['fl']}, 'photoshop_render_source': {'type': 'str', 'choices': ['ps']}, 'afterfx_render_source': {'type': 'str', 'choices': ['ae']}, 'blender_render_source': {'type': 'str', 'choices': ['bl']}, 'harmony_render_source': {'type': 'str', 'choices': ['ha']}, 'houdini_render_source': {'type': 'str', 'choices': ['htoa', 'mantra']}, 'footage_source': {'type': 'str'}, 'colorspace': {'type': 'str'}, 'write_node': {'type': 'str'}, 'write_node_parent': {'type': 'str'}, 'node': {'type': 'str'}, 'segment_name': {'type': 'str'}, 'export_ass_set_suffix': {'type': 'str'}, 'export_ass_top_namespace': {'type': 'str'}, 'export_fur_top_namespace': {'type': 'str'}, 'camera': {'type': 'str'}, 'cache_variant': {'type': 'str'}, 'image_variant': {'type': 'str'}, 'extra_variant': {'type': 'str'}, 'vendor': {'type': 'str'}, 'package_type': {'type': 'str'}}";
	
	std::string paths = "{'rootDir': 'D:/Desk/python/Tank/tests/project','sequence_root':'@sequence/{Sequence}', 'shot_root':'@sequence_root/{Shot}'," \
	                    "'shot_task_root':'@shot_root/{Task}','Shot_Image_WorkArea':'@shot_task_root/image/wip'," \
						"'generic_image_dirname_nuke':'{name}-{Task}-{variant}-{render_source}-{write_node}-v{version}-{colorspace}-{ext_render_nuke}',"\
						"'Shot_NukeRender_Work_Generic_Name':'@Shot_Image_WorkArea/@generic_image_dirname_nuke',"\
						"'Shot_NukeRender_Work_Sequence':'@Shot_NukeRender_Work_Generic_Name/@nuke_image_name.{SEQ}.{ext_render_nuke}'";
	std::string strs = "{'nuke_image_name':'{name}-{Task}-{variant}-{render_source}-{write_node}-v{version}-{colorspace}', 'generic_version_name':'{name}-{Task}-{variant}-v{version}'}";

	std::map<std::string, std::string> strsDict;
	std::map<std::string, std::string> pathsDict;
	std::map<std::string, std::map<std::string, std::string>> keysDict;
	// pathsDict = generatePathsDictionnaryFromString(paths);
	// keysDict  = generateKeysDictionnaryFromString(keys);
	// strsDict  = generateStringsDictionnaryFromString(strs);

	// std::cout << "Strings" << std::endl;
	// for (const auto& key : strsDict) {
    //     std::cout << key.first << ":" << key.second << std::endl;	
	// }
	// std::cout << " " << std::endl;

	// std::cout << "Paths" << std::endl;
	// for (const auto& key : pathsDict) {
    //     std::cout << key.first << ":" << key.second << std::endl;
	// }
	// std::cout << " " << std::endl;
	// std::cout << "" << std::endl;
	// std::cout << "Keys" << std::endl;
	// for (const auto& key : keysDict) {
    //     std::cout << key.first << ":" << std::endl;
    //     for (const auto& subkey : key.second) {
    //         std::cout << "    " << subkey.first << ":" << subkey.second << std::endl;
    //     }
	// }
	std::cout << " Get Keys " << std::endl;
	std::cout << "" << std::endl;
	
	Tank tank_test(paths, keys, strs);
	std::map<std::string, TemplatePath> templates =  tank_test.getTemplates();
	std::cout << tank_test.getAllKeys().size() << std::endl;
	std::cout << "" << std::endl;
	for(const auto& key : tank_test.getAllKeys()) {
		const std::string& cle = key.first;
		const std::string& valeur = key.second->getDefault();
		std::cout << cle << " : " << valeur << std::endl;
	}

	std::cout << "" << std::endl;
	for (const auto& paire : templates) {
		const std::string& cle = paire.first;
        const std::string& valeur = paire.second.getDefinition();
		std::cout << cle << " : " << valeur << std::endl;
	}

	std::cout << "" << std::endl;
	TemplatePath nuke_tpl = templates["Shot_NukeRender_Work_Sequence"];
	// std::cout << "definition" << std::endl;
	// std::cout << nuke_tpl.getDefinition() << std::endl;
	// // std::cout << "" << std::endl;
	// // std::vector<std::string> test = nuke_tpl.getOrderedKeys();
	// // for(int i=0; i<test.size(); i++){	
	// // 	std::cout << test[i] << std::endl;
	// // }
	// std::cout << "" << std::endl;
	std::cout << "testpath" << std::endl;
	std::string testpath = nuke_tpl.apply_fields(fields);
	std::cout << testpath << std::endl;

	// std::cout << "" << std::endl;
	// std::vector<std::string> test = nuke_tpl.missingKeys(fields);
	// std::cout << "Missing keys" << std::endl;
	// for(int i=0; i<test.size(); i++){
	// 	std::cout << test[i] << std::endl;
	// }


	// std::string path = "D:/Desk/python/Tank/tests/project/test/sh_010/cmp/nuke/sh_010-cmp-base-v1.nk";
	
	// std::cout << "" << std::endl;
	// std::cout << "Get Fields" << std::endl;
	// std::map<std::string, std::string> get_fields = nuke_tpl.getFields(path);
	// for (const auto& paire : get_fields) {
	// 	const std::string& cle = paire.first;
    //     const std::string& valeur = paire.second;
	// 	std::cout << cle << " : " << valeur << std::endl;
	// }
	


	// std::cout << "D:\\Desk\\python\\Tank\\tests\\project" << std::endl;
	// std::cout << pattern_test << std::endl;
	// std::vector<std::string> abspathsTest2 = listFilesFromPathPattern("D:\\Desk\\python\\Tank\\tests\\project", pattern_test);

	// std::cout << "" << std::endl;
	// std::vector<std::string> abspathsTest = tank_test.getAbstractPathsFromTemplate(nuke_tpl, fields);
	// std::cout << "" << std::endl;
	// for(int i=0; i<abspathsTest.size(); i++){
	// 	std::cout << "match  " << abspathsTest[i] << std::endl;
	// }
	// std::cout << "" << std::endl;
    

	// TemplatePath aTesty = tank_test.templateFromPath(testpath);
	// std::cout << testpath << std::endl;
	// std::cout << aTesty.getName() << std::endl;
	// std::cout << aTesty.getDefinition() << std::endl;
	// // std::cout << aTesty.getOrderedKeys() << std::endl;
	// std::cout << " " <<std::endl;

	// std::vector<std::string> etfiel = aTesty.getStaticTokens();
	// for (int i=0; i<etfiel.size(); i++) {
    //     std::cout << etfiel[i] << std::endl ;
    // }
	// std::cout << " " <<std::endl;
	// for (const auto& paire : aTesty.getFields(testpath)) {
	// 	const std::string& cle = paire.first;
    //     const std::string& valeur = paire.second;
	// 	std::cout << cle << " : " << valeur << std::endl;
	// }
	// TemplatePath aTestya = tank_test.templateFromPath(testpathNot);
	// std::cout << aTestya.getName() << std::endl;
	// TemplatePath aTestyaa = tank_test.templateFromPath(testpathGood);
	// std::cout << aTestyaa.getName() << std::endl;

	// std::cout << nuke_tpl.validate(testpathNot) << std::endl;
	
	// std::cout << nuke_tpl.getName() << " " << nuke_tpl.getDefinition() << std::endl;

    // créer le dictionnaire "keys"
	//std::string keys = argv[1];
    //Templates templatesTest(pathsdict, keydict);
	//for (auto a = templatesTest.templates.begin(); a != templatesTest.templates.end(); ++a) {
	//	std::cout << a->first << "  " << a->second.getDefinition() << std::endl;
	//}
    
    //if (argc>2) return 0;

    return 1;

}

