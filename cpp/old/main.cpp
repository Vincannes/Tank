#include <map>
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip> // Pour setw

#include "template_obj.h"
#include "tank_obj.h"

int main() {
    std::string config = "D:\\Desk\\python\\Tank\\config\\templates.yml";

	std::string keysOLD  = "{'Root' : {'type': 'str'}, 'dir' : {'type': 'str'}, 'Shot' : {'type': 'str', 'choices':['sh_030', 'sh_040']}, 'version' : {'alias':'version', 'type': 'int', 'default': '1', 'format_spec: '03'}, 'Task' : {'type': 'str', 'default': 'aa'}";
	std::string pathsOLD = "{'rootDir': 'D:\\Desk\\python\\Tank\\tests\\project', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}', 'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', 'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}";
	
	std::string keys = "{'Sequence': {'type': 'str', 'filter_by': '^(?!_InvalidName_)\\w+$'}, 'Shot': {'type': 'str', 'filter_by': '^(?!_InvalidName_)\\w+$'}, 'Step': {'type': 'str'}, 'sg_asset_type': {'type': 'str'}, 'Asset': {'type': 'str', 'filter_by': '^(?!_InvalidName_)\\w+$'}, 'name': {'type': 'str', 'filter_by': '\\w+'}, 'iteration': {'type': 'int'}, 'version': {'type': 'int', 'format_spec': '03'}, 'version_four': {'type': 'int', 'format_spec': '04', 'alias': 'version'}, 'special_version': {'type': 'str', 'filter_by': '^(last|valid)$'}, 'timestamp': {'type': 'str'}, 'width': {'type': 'int'}, 'height': {'type': 'int'}, 'shot_client_review_name': {'type': 'str'}, 'playlist_name': {'type': 'str'}, 'path_additional': {'type': 'str'}, 'project_resolution': {'type': 'str', 'filter_by': '^[^\\.]+$'}, 'slate_frame': {'type': 'sequence', 'format_spec': '04'}, 'delivery_image_type': {'type': 'str'}, 'client_step': {'type': 'str'}, 'delivery_quicktime_suffix': {'type': 'str'}, 'cut_name': {'type': 'str'}, 'cut_revision': {'type': 'int'}, 'tool': {'type': 'str'}, 'output': {'alias': 'nuke.output', 'type': 'str', 'filter_by': 'alphanumeric'}, 'SEQ': {'type': 'sequence', 'format_spec': '04'}, 'HSEQ': {'type': 'sequence', 'format_spec': '04', 'default': 'FORMAT: $F'}, 'eye': {'type': 'str', 'choices': ['left', 'right']}, 'houdini.node': {'alias': 'node', 'type': 'str'}, 'golaem_node': {'type': 'str'}, 'aov_name': {'type': 'str'}, 'YYYY': {'type': 'int', 'format_spec': '04'}, 'MM': {'type': 'int', 'format_spec': '02'}, 'DD': {'type': 'int', 'format_spec': '02', 'alias': 'DD'}, 'project': {'type': 'str'}, 'UDIM': {'type': 'sequence', 'default': '<UDIM>'}, 'mari.channel': {'type': 'str', 'alias': 'channel'}, 'mari.layer': {'type': 'str', 'alias': 'layer'}, 'mari.project_name': {'type': 'str', 'alias': 'name'}, 'layer': {'type': 'str'}, 'asset_name': {'type': 'str', 'shotgun_entity_type': 'Asset', 'shotgun_field_name': 'code'}, 'task_name': {'type': 'str', 'shotgun_entity_type': 'Task', 'shotgun_field_name': 'content'}, 'distribution_index': {'type': 'str'}, 'distribution_type': {'type': 'str'}, 'Task': {'type': 'str'}, 'render_iteration': {'type': 'int', 'format_spec': '03'}, 'variant': {'type': 'str', 'default': 'base'}, 'extension': {'type': 'str', 'filter_by': '^[a-zA-Z0-9]{1,5}$'}, 'render_layer': {'type': 'str', 'filter_by': '^[^.]+$'}, 'render_aov': {'type': 'str'}, 'clarisse_image': {'type': 'str'}, 'clarisse_layer': {'type': 'str'}, 'image_ext': {'type': 'str', 'choices': ['jpg', 'png', 'exr']}, 'ext_render_nuke': {'choices': ['jpg', 'dpx', 'png', 'exr', 'tiff', 'mov', 'tga'], 'type': 'str'}, 'ext_render_flame': {'choices': ['jpg', 'dpx', 'exr', 'tiff', 'tga'], 'type': 'str'}, 'ext_cache_houdini': {'choices': ['abc', 'ass', 'ifd', 'bhclassic', 'bgeo', 'bgeo.sc', 'obj', 'vdb'], 'type': 'str'}, 'ext_proxy': {'type': 'str', 'choices': ['jpg', 'png', 'exr'], 'default': 'jpg'}, 'ext_scene_photoshop': {'choices': ['psd', 'psb'], 'type': 'str'}, 'cache_type_houdini': {'type': 'str', 'choices': ['abc', 'ass', 'ifd', 'bhclassic', 'bgeo', 'obj', 'vdb']}, 'ext_render_clarisse': {'choices': ['jpg', 'bmp', 'png', 'exr', 'tiff', 'tga'], 'type': 'str'}, 'ext_render_afterfx': {'choices': ['jpg', 'png', 'exr', 'tiff'], 'type': 'str'}, 'ext_render_blender': {'choices': ['jpg', 'png', 'exr', 'tiff'], 'type': 'str'}, 'ext_render_c4d': {'choices': ['exr', 'tiff', 'jpg', 'png'], 'type': 'str'}, 'ext_cache_maya': {'choices': ['abc', 'ass', 'fur', 'vdb'], 'type': 'str'}, 'render_source': {'type': 'str', 'choices': ['mtoa', 'nk', 'nkelem', 'nkcache', 'nkmatte', 'ps', 'c4dtoa']}, 'flame_render_source': {'type': 'str', 'choices': ['fl']}, 'photoshop_render_source': {'type': 'str', 'choices': ['ps']}, 'afterfx_render_source': {'type': 'str', 'choices': ['ae']}, 'blender_render_source': {'type': 'str', 'choices': ['bl']}, 'harmony_render_source': {'type': 'str', 'choices': ['ha']}, 'houdini_render_source': {'type': 'str', 'choices': ['htoa', 'mantra']}, 'footage_source': {'type': 'str'}, 'colorspace': {'type': 'str'}, 'write_node': {'type': 'str'}, 'write_node_parent': {'type': 'str'}, 'node': {'type': 'str'}, 'segment_name': {'type': 'str'}, 'export_ass_set_suffix': {'type': 'str'}, 'export_ass_top_namespace': {'type': 'str'}, 'export_fur_top_namespace': {'type': 'str'}, 'camera': {'type': 'str'}, 'cache_variant': {'type': 'str'}, 'image_variant': {'type': 'str'}, 'extra_variant': {'type': 'str'}, 'vendor': {'type': 'str'}, 'package_type': {'type': 'str'}}";
	std::string paths = "{'sequence_root': '@prod_root/sequence/{Sequence}', 'shot_root': '@sequence_root/{Shot}', 'shot_task_root': '@shot_root/{Task}', 'asset_root': 'asset/{sg_asset_type}/{Asset}', 'asset_task_root': '@asset_root/{Task}', 'hiero_project_work_area': 'office/coordination/lab_playlist/wip', 'hiero_project_work': '@hiero_project_work_area/{name}-v{version}.hrox', 'hiero_project_snapshot': '@hiero_project_work_area/snapshots/{name}-v{version}-{timestamp}.hrox', 'hiero_project_publish_area': 'office/coordination/lab_playlist/publish', 'hiero_project_publish': '@hiero_project_publish_area/{name}-v{version}.hrox', 'hiero_log_dispatch': 'office/coordination/log_dispatch', 'Sequence_Cut_Media': 'sequence/common/cuts/{cut_name}/{cut_name}-{cut_revision}.mov', 'Shot_Sound_Dir': '@shot_root/common/sound', 'Shot_Camera_Dir': '@shot_root/common/camera', 'Shot_Camera_File': '@Shot_Camera_Dir/{Shot}-{variant}-v{version}.{extension}', 'Shot_Image_WorkArea': '@shot_task_root/image/wip', 'Shot_Image_PublishArea': '@shot_task_root/image/publish', 'Shot_Media_Default': '@Shot_Image_WorkArea/{name}.{SEQ}.mov', 'Shot_Image_Publish': '@Shot_Image_PublishArea/{Shot}-{Task}-base-v{version}-{tool}/{Shot}-{Task}-base-v{version}-{colorspace}.{SEQ}.{extension}', 'Shot_Cache_Area': '@shot_root/{Task}/cache', 'Shot_Cache_Area_Secondary': '@shot_root/{Task}/cache', 'Shot_Cache_Work_Area': '@Shot_Cache_Area/wip', 'Shot_Cache_Work_Area_Secondary': '@Shot_Cache_Area_Secondary/wip', 'Shot_Cache_Publish_Area': '@Shot_Cache_Area/publish', 'Shot_Cache_Publish_Area_Secondary': '@Shot_Cache_Area_Secondary/publish', 'Playlist_Delivery_Area': 'io/out', 'Sequence_Def_Delivery_Area': '@Playlist_Delivery_Area/to_lab/{playlist_name}/@client_shot_name', 'Sequence_Def_Delivery': '@Sequence_Def_Delivery_Area/[{project_resolution}]/@client_shot_name.{SEQ}.{delivery_image_type}', 'Quicktime_Delivery': '@Playlist_Delivery_Area/to_edit/{playlist_name}/[{path_additional}/][{project_resolution}/]@client_shot_name[_{delivery_quicktime_suffix}].mov', 'Proxy_Delivery': '@Playlist_Delivery_Area/to_edit/{playlist_name}/[{path_additional}/][{project_resolution}/]@client_shot_name[_{delivery_quicktime_suffix}].{SEQ}.jpg', 'Matte_Delivery_Area': '@Playlist_Delivery_Area/to_lab/{playlist_name}/@client_shot_name_matte', 'Matte_Delivery': '@Matte_Delivery_Area/@client_shot_name_matte.{SEQ}.{delivery_image_type}', 'Nuke_Template_Out_Media': '_admin/io/out_media.nk', 'To_Vendor_Root_Folder': 'io/out/to_vendor', 'From_Vendor_Root_Folder': 'io/in/from_vendor', 'To_Vendor_Folder': '@To_Vendor_Root_Folder/{vendor}', 'From_Vendor_Folder': '@From_Vendor_Root_Folder/{vendor}/{package_type}/{timestamp}', 'Shot_Flame_ExportArea': '@shot_task_root/flame', 'flame_segment_clip': '@shot_root/finish/flame/clip/sources/{Shot}-{Task}-{variant}-v{version}.clip', 'flame_shot_clip': '@shot_root/finish/flame/clip/{Shot}-{variant}-out.clip', 'flame_shot_batch': '@shot_root/finish/flame/batch/{Shot}-{variant}-v{version}.batch', 'Shot_FlameRender_Work_Generic_Name': '@Shot_Image_WorkArea/@generic_image_dirname_flame', 'Shot_FlameRender_Work_Sequence': '@Shot_FlameRender_Work_Generic_Name/@flame_image_name.{SEQ}.{ext_render_flame}', 'Shot_MayaScene_ProjectArea': '@shot_root/{Task}/maya', 'Shot_MayaScene_WorkArea': '@Shot_MayaScene_ProjectArea/wip', 'Shot_MayaScene_PublishArea': '@Shot_MayaScene_ProjectArea/publish', 'Shot_MayaScene_Work': '@Shot_MayaScene_WorkArea/@generic_version_name.ma', 'maya_shot_work_render': '@Shot_MayaScene_WorkArea/renders/@generic_version_name{render_iteration}.mb', 'Shot_MayaScene_Snapshot': '@Shot_MayaScene_WorkArea/snapshots/@generic_version_name.{timestamp}.ma', 'Shot_MayaScene_Publish': '@Shot_MayaScene_PublishArea/@generic_version_name.ma', 'Shot_MayaScene_PublishSpecial': '@Shot_MayaScene_PublishArea/{name}-{Task}-{variant}-{special_version}.ma', 'Shot_MayaRender_Work_Generic_Name': '@Shot_Image_WorkArea/@generic_image_dirname', 'Shot_MayaRender_Work_Layer': '@Shot_MayaRender_Work_Generic_Name/{render_layer}', 'Shot_MayaRender_Work_Aov': '@Shot_MayaRender_Work_Layer/{render_aov}', 'Shot_MayaRender_Work_Sequence': '@Shot_MayaRender_Work_Aov/@generic_version_name-{render_layer}-{render_aov}-{colorspace}.{SEQ}.{image_ext}', 'Shot_MayaRender_Publish_Generic_Name': '@Shot_Image_PublishArea/@generic_image_dirname', 'Shot_MayaRender_Publish_Layer': '@Shot_MayaRender_Publish_Generic_Name/{render_layer}', 'Shot_MayaRender_Publish_Aov': '@Shot_MayaRender_Publish_Layer/{render_aov}', 'Shot_MayaRender_Publish_Sequence': '@Shot_MayaRender_Publish_Aov/@generic_version_name-{render_layer}-{render_aov}-{colorspace}.{SEQ}.{image_ext}', 'Shot_MayaBlast_Work_Generic_Name': '@Shot_Image_WorkArea/@generic_version_name-blast-{colorspace}', 'Shot_MayaBlast_Work_Camera': '@Shot_MayaBlast_Work_Generic_Name/{camera}', 'Shot_MayaBlast_Work_Sequence': '@Shot_MayaBlast_Work_Camera/@generic_version_name_colorspace-{camera}.{SEQ}.{image_ext}', 'Shot_MayaBlast_Publish_Generic_Name': '@Shot_Image_PublishArea/@generic_version_name-blast', 'Shot_MayaBlast_Publish_Camera': '@Shot_MayaBlast_Publish_Generic_Name/{camera}', 'Shot_MayaBlast_Publish_Sequence': '@Shot_MayaBlast_Publish_Camera/@generic_version_name_colorspace-{camera}.{SEQ}.{image_ext}', 'Rancher_Job_Root': '@shot_root/common/rancher/{Task}', 'Rancher_Asset_Job_Root': '@asset_root/common/rancher/{Task}', 'Arnold_MayaRenderCache': '@Shot_Cache_Work_Area/ass/@generic_cache_version_name-maya/@generic_cache_version_name.ass.gz', 'Shot_AlembicCache_Work_File': '@Shot_Cache_Work_Area/abc/@generic_cache_version_name-{tool}/@generic_cache_version_name.abc', 'Shot_AlembicCache_Work_File_Secondary': '@Shot_Cache_Work_Area_Secondary/abc/@generic_cache_version_name-{tool}/@generic_cache_version_name.abc', 'Shot_AlembicCache_Publish_File': '@Shot_Cache_Publish_Area/abc/@generic_cache_version_name-{tool}/@generic_cache_version_name.abc', 'Shot_AlembicCache_Publish_File_Secondary': '@Shot_Cache_Publish_Area_Secondary/abc/@generic_cache_version_name-{tool}/@generic_cache_version_name.abc', 'Shot_YetiCache_Work_File': '@Shot_Cache_Work_Area/fur/@generic_cache_version_name-maya/@generic_cache_version_name.{SEQ}.fur', 'Shot_YetiCache_Publish_File': '@Shot_Cache_Publish_Area/fur/@generic_cache_version_name-maya/@generic_cache_version_name.{SEQ}.fur', 'Shot_YetiDescription_File': '@shot_root/common/hair_shot_description.json', 'Shot_GolaemCache_Work_Area': '@Shot_Cache_Work_Area_Secondary/golaem', 'Shot_GolaemCache_Work_Area_Simulation': '@Shot_GolaemCache_Work_Area/@generic_golaem_cache_version_name', 'Shot_GolaemCache_Simulation_Frame_Work_File': '@Shot_GolaemCache_Work_Area_Simulation/@generic_golaem_cache_version_name.{golaem_node}.{SEQ}.gscf', 'Shot_GolaemCache_Simulation_Work_File': '@Shot_GolaemCache_Work_Area_Simulation/@generic_golaem_cache_version_name.{golaem_node}.gscs', 'Shot_GolaemLibrary_Work_File': '@Shot_GolaemCache_Work_Area_Simulation/@generic_golaem_cache_version_name.gscb', 'Shot_HoudiniScene_WorkArea': '@shot_root/{Task}/houdini/wip', 'Shot_HoudiniScene_PublishArea': '@shot_root/{Task}/houdini/publish', 'Shot_HoudiniScene_ProjectArea': '@shot_root/{Task}/houdini', 'Shot_HoudiniCache_PrivateArea': '@Shot_HoudiniScene_WorkArea/@generic_version_name', 'Shot_HoudiniScene_Work': '@Shot_HoudiniScene_WorkArea/@generic_version_name.hip', 'Shot_HoudiniScene_Snapshot': '@Shot_HoudiniScene_WorkArea/snapshots/@generic_version_name.{timestamp}.hip', 'Shot_HoudiniScene_Publish': '@Shot_HoudiniScene_PublishArea/@generic_version_name.hip', 'Shot_HoudiniScene_PublishSpecial': '@Shot_HoudiniScene_PublishArea/{name}-{Task}-{variant}-{special_version}.hip', 'Shot_HoudiniRender_Work_Generic_Name': '@Shot_Image_WorkArea/@generic_image_dirname_houdini', 'Shot_HoudiniRender_Work_Aov': '@Shot_HoudiniRender_Work_Generic_Name/{render_aov}', 'Shot_HoudiniRender_Work_Sequence': '@Shot_HoudiniRender_Work_Aov/@generic_houdini_version_name-{render_aov}.{HSEQ}.{image_ext}', 'Shot_HoudiniRender_Work_Distributed_Sequence': '@Shot_HoudiniRender_Work_Aov/{distribution_type}_{distribution_index}/@generic_houdini_version_name-{render_aov}.{distribution_type}_{distribution_index}.{HSEQ}.{image_ext}', 'Shot_HoudiniRender_Publish_Generic_Name': '@Shot_Image_PublishArea/@generic_image_dirname_houdini', 'Shot_HoudiniRender_Publish_Aov': '@Shot_HoudiniRender_Publish_Generic_Name/{render_aov}', 'Shot_HoudiniRender_Publish_Sequence': '@Shot_HoudiniRender_Publish_Aov/@generic_houdini_version_name-{render_aov}.{HSEQ}.{image_ext}', 'Shot_HoudiniRender_Publish_Distributed_Sequence': '@Shot_HoudiniRender_Publish_Aov/{distribution_type}_{distribution_index}/@generic_houdini_version_name-{render_aov}.{distribution_type}_{distribution_index}.{HSEQ}.{image_ext}', 'Shot_HoudiniCache_Work_Sequence': '@Shot_Cache_Work_Area_Secondary/{cache_type_houdini}/@generic_cache_version_name-houdini/@generic_cache_version_name.{HSEQ}.{ext_cache_houdini}', 'Shot_HoudiniCache_Work_File': '@Shot_Cache_Work_Area_Secondary/{cache_type_houdini}/@generic_cache_version_name-houdini/@generic_cache_version_name.{ext_cache_houdini}', 'Shot_HoudiniCache_Work_Distributed_Sequence': '@Shot_Cache_Work_Area_Secondary/{cache_type_houdini}/@generic_cache_version_name-houdini/{distribution_type}_{distribution_index}/@generic_cache_version_name.{distribution_type}_{distribution_index}.{HSEQ}.{ext_cache_houdini}', 'Shot_HoudiniCache_Work_Distributed_File': '@Shot_Cache_Work_Area_Secondary/{cache_type_houdini}/@generic_cache_version_name-houdini/{distribution_type}_{distribution_index}/@generic_cache_version_name.{distribution_type}_{distribution_index}.{ext_cache_houdini}', 'Shot_HoudiniCache_Work_Checkpoints_Sequence': '@Shot_Cache_Work_Area_Secondary/{cache_type_houdini}/@generic_cache_version_name-houdini/sim/@generic_version_name.@HSIMSEQ.sim', 'Shot_HoudiniCache_Private_Sequence': '@Shot_HoudiniCache_PrivateArea/{cache_type_houdini}/@generic_cache_version_name/@generic_cache_version_name.{HSEQ}.{ext_cache_houdini}', 'Shot_HoudiniCache_Private_File': '@Shot_HoudiniCache_PrivateArea/{cache_type_houdini}/@generic_cache_version_name/@generic_cache_version_name.{ext_cache_houdini}', 'Shot_HoudiniCache_Private_Distributed_Sequence': '@Shot_HoudiniCache_PrivateArea/{cache_type_houdini}/@generic_cache_version_name/{distribution_type}_{distribution_index}/@generic_cache_version_name.{distribution_type}_{distribution_index}.{HSEQ}.{ext_cache_houdini}', 'Shot_HoudiniCache_Private_Distributed_File': '@Shot_HoudiniCache_PrivateArea/{cache_type_houdini}/@generic_cache_version_name/{distribution_type}_{distribution_index}/@generic_cache_version_name.{distribution_type}_{distribution_index}.{ext_cache_houdini}', 'Shot_HoudiniCache_Private_Checkpoints_Sequence': '@Shot_HoudiniCache_PrivateArea/{cache_type_houdini}/@generic_cache_version_name/sim/@generic_cache_version_name.@HSIMSEQ.sim', 'Shot_HoudiniCache_Publish_Sequence': '@Shot_Cache_Publish_Area_Secondary/{cache_type_houdini}/@generic_cache_version_name-houdini/@generic_cache_version_name.{HSEQ}.{ext_cache_houdini}', 'Shot_HoudiniCache_Publish_File': '@Shot_Cache_Publish_Area_Secondary/{cache_type_houdini}/@generic_cache_version_name-houdini/@generic_cache_version_name.{ext_cache_houdini}', 'Shot_HoudiniCache_Publish_Distributed_Sequence': '@Shot_Cache_Publish_Area_Secondary/{cache_type_houdini}/@generic_cache_version_name-houdini/{distribution_type}_{distribution_index}/@generic_cache_version_name.{distribution_type}_{distribution_index}.{HSEQ}.{ext_cache_houdini}', 'Shot_HoudiniCache_Publish_Distributed_File': '@Shot_Cache_Publish_Area_Secondary/{cache_type_houdini}/@generic_cache_version_name-houdini/{distribution_type}_{distribution_index}/@generic_cache_version_name.{distribution_type}_{distribution_index}.{ext_cache_houdini}', 'Shot_HoudiniFlip_Work_Generic_Name': '@Shot_Image_WorkArea/@generic_version_name-flip', 'Shot_HoudiniFlip_Work_Camera': '@Shot_HoudiniFlip_Work_Generic_Name/{camera}', 'Shot_HoudiniFlip_Work_Sequence': '@Shot_HoudiniFlip_Work_Camera/@generic_version_name-{camera}.{HSEQ}.{image_ext}', 'Shot_HoudiniFlip_Publish_Generic_Name': '@Shot_Image_PublishArea/@generic_version_name-flip', 'Shot_HoudiniFlip_Publish_Camera': '@Shot_HoudiniFlip_Publish_Generic_Name/{camera}', 'Shot_HoudiniFlip_Publish_Sequence': '@Shot_HoudiniFlip_Publish_Camera/@generic_version_name-{camera}.{HSEQ}.{image_ext}', 'Shot_ClarisseScene_ProjectArea': '@shot_root/{Task}/clarisse', 'Shot_ClarisseScene_WorkArea': '@Shot_ClarisseScene_ProjectArea/wip', 'Shot_ClarisseScene_Work': '@Shot_ClarisseScene_WorkArea/@generic_version_name.project', 'Shot_ClarisseScene_Snapshot': '@Shot_ClarisseScene_WorkArea/snapshots/@generic_version_name.{timestamp}.project', 'Shot_ClarisseScene_PublishArea': '@Shot_ClarisseScene_ProjectArea/publish', 'Shot_ClarisseScene_Publish': '@Shot_ClarisseScene_PublishArea/@generic_version_name.project', 'Shot_ClarisseScene_PublishSpecial': '@Shot_ClarisseScene_PublishArea/{name}-{Task}-{variant}-{special_version}.project', 'Shot_ClarisseRender_Work_Generic_Name': '@Shot_Image_WorkArea/@generic_version_name-clarisse', 'Shot_ClarisseRender_Work_Image': '@Shot_ClarisseRender_Work_Generic_Name/{clarisse_image}', 'Shot_ClarisseRender_Work_Layer': '@Shot_ClarisseRender_Work_Image/{clarisse_layer}', 'Shot_ClarisseRender_Work_Sequence': '@Shot_ClarisseRender_Work_Layer/@generic_version_name-{clarisse_image}-{clarisse_layer}-{colorspace}.{SEQ}.{ext_render_clarisse}', 'Shot_ClarisseRender_Publish_Generic_Name': '@Shot_Image_PublishArea/@generic_version_name-clarisse', 'Shot_ClarisseRender_Publish_Image': '@Shot_ClarisseRender_Publish_Generic_Name/{clarisse_image}', 'Shot_ClarisseRender_Publish_Layer': '@Shot_ClarisseRender_Publish_Image/{clarisse_layer}', 'Shot_ClarisseRender_Publish_Sequence': '@Shot_ClarisseRender_Publish_Layer/@generic_version_name-{clarisse_image}-{clarisse_layer}-{colorspace}.{SEQ}.{ext_render_clarisse}', 'Shot_C4dScene_ProjectArea': '@shot_root/{Task}/c4d', 'Shot_C4dScene_WorkArea': '@Shot_C4dScene_ProjectArea/wip', 'Shot_C4dScene_Work': '@Shot_C4dScene_WorkArea/@generic_version_name.c4d', 'Shot_C4dScene_PublishArea': '@Shot_C4dScene_ProjectArea/publish', 'Shot_C4dScene_Publish': '@Shot_C4dScene_PublishArea/@generic_version_name.c4d', 'Shot_C4dScene_PublishSpecial': '@Shot_C4dScene_PublishArea/{name}-{Task}-{variant}-{special_version}.c4d', 'Shot_C4dRender_Work_Generic_Name': '@Shot_Image_WorkArea/@generic_image_dirname_c4d', 'Shot_C4dRender_Work_Aov': '@Shot_C4dRender_Work_Generic_Name/{render_aov}', 'Shot_C4dRender_Work_Sequence': '@Shot_C4dRender_Work_Aov/@generic_version_name_c4d_{render_aov}.{SEQ}.{ext_render_c4d}', 'Shot_C4dRender_Publish_Generic_Name': '@Shot_Image_PublishArea/@generic_image_dirname_c4d', 'Shot_C4dRender_Publish_Aov': '@Shot_C4dRender_Publish_Generic_Name/{render_aov}', 'Shot_C4dRender_Publish_Sequence': '@Shot_C4dRender_Publish_Aov/@generic_version_name_c4d.{SEQ}.{ext_render_c4d}', 'Shot_NukeScene_WorkArea': '@shot_root/{Task}/nuke/wip', 'Shot_NukeScene_PublishArea': '@shot_root/{Task}/nuke/publish', 'Shot_NukeScene_Work': '@Shot_NukeScene_WorkArea/@generic_version_name.nk', 'nuke_shot_thumbnail': '@Shot_Image_WorkArea/@generic_version_name.png', 'nuke_shot_thumbnail_pub': '@Shot_Image_PublishArea/@generic_version_name.png', 'Sequence_NukeScene_Degrain': '@sequence_root/common/dgn/{Sequence}-v{version}.nk', 'Shot_NukeRender_Work_Generic_Name': '@Shot_Image_WorkArea/@generic_image_dirname_nuke', 'Shot_NukeRender_Work_Sequence': '@Shot_NukeRender_Work_Generic_Name/@nuke_image_name.{SEQ}.{ext_render_nuke}', 'Shot_NukeRender_Publish_Generic_Name': '@Shot_Image_PublishArea/@generic_image_dirname_nuke', 'Shot_NukeRender_Publish_Sequence': '@Shot_NukeRender_Publish_Generic_Name/@nuke_image_name.{SEQ}.{ext_render_nuke}', 'Shot_NukeRender_Publish_Movie': '@Shot_NukeRender_Publish_Generic_Name.mov', 'Shot_NukeProxy_Work_Sequence': '@Shot_Image_WorkArea/@nuke_image_name-pxy/@nuke_image_name.{SEQ}.{ext_proxy}', 'Element_NukeRender_Root': 'image/elements/{write_node}', 'Element_NukeRender_Generic_Name': 'image/elements/{write_node}/@generic_image_dirname_nuke', 'Shot_Element_NukeRender_Root': '@shot_task_root/@Element_NukeRender_Root', 'Shot_Element_NukeRender_Generic_Name': '@shot_task_root/@Element_NukeRender_Generic_Name', 'Shot_Element_NukeRender_Sequence': '@Shot_Element_NukeRender_Generic_Name/@nuke_image_name.{SEQ}.{ext_render_nuke}', 'hiero_plate_path': '@shot_root/common/sources_vfx/{YYYY}_{MM}_{DD}/plates/{project}_{Sequence}_{name}.mov', 'hiero_render_path': '@shot_root/common/sources_vfx/{YYYY}_{MM}_{DD}/renders/{project}_{Sequence}_{name}.{SEQ}.dpx', 'Hiero_Footage_Root': '@shot_root/common/footage/{Shot}-{Task}-{variant}-v{version}-{colorspace}-{extension}', 'Hiero_Footage_Sequence': '@Hiero_Footage_Root/{Shot}-{Task}-{variant}-v{version}-{colorspace}.{SEQ}.{extension}', 'Shot_PhotoshopScene_ProjectArea': '@shot_root/{Task}/photoshop', 'Shot_PhotoshopScene_WorkArea': '@Shot_PhotoshopScene_ProjectArea/wip', 'Shot_PhotoshopScene_Work': '@Shot_PhotoshopScene_WorkArea/@generic_version_name.{ext_scene_photoshop}', 'Shot_PhotoshopScene_PublishArea': '@Shot_PhotoshopScene_ProjectArea/publish', 'Shot_PhotoshopScene_Publish': '@Shot_PhotoshopScene_PublishArea/@generic_version_name.{ext_scene_photoshop}', 'Shot_PhotoshopScene_PublishSpecial': '@Shot_PhotoshopScene_PublishArea/{name}-{Task}-{variant}-{special_version}.{ext_scene_photoshop}', 'Shot_PhotoshopRender_Work_Image': '@Shot_Image_WorkArea/@photoshop_image_name.{extension}', 'Shot_PhotoshopRender_Publish_Image': '@Shot_Image_PublishArea/@photoshop_image_name.{extension}', 'Shot_HarmonyRender_Work_Image': '@Shot_Image_WorkArea/@harmony_image_name-{image_ext}/@harmony_image_name.{SEQ}.{image_ext}', 'Shot_HarmonyRender_Publish_Image': '@Shot_Image_PublishArea/@harmony_image_name-{image_ext}/@harmony_image_name.{SEQ}.{image_ext}', 'Shot_AfterfxRender_Work_Generic_Name': '@Shot_Image_WorkArea/@generic_image_dirname_afterfx', 'Shot_AfterfxRender_Work_Sequence': '@Shot_AfterfxRender_Work_Generic_Name/@afterfx_image_name.{SEQ}.{ext_render_afterfx}', 'Shot_BlenderRender_Work_Generic_Name': '@Shot_Image_WorkArea/@generic_image_dirname_blender', 'Shot_BlenderRender_Work_Sequence': '@Shot_BlenderRender_Work_Generic_Name/@blender_image_name.{SEQ}.{ext_render_blender}', 'Asset_Image_PublishArea': '@asset_root/{Task}/image/publish', 'Asset_Image_WorkArea': '@asset_root/{Task}/image/wip', 'Asset_Media_Default': '@Asset_Image_WorkArea/{name}.{SEQ}.mov', 'Asset_Image_Publish': '@Asset_Image_PublishArea/{Asset}-{Task}-base-v{version}-{tool}/{Asset}-{Task}-base-v{version}-{colorspace}.{SEQ}.{extension}', 'Asset_Cache_Area': '@asset_root/{Task}/cache', 'Asset_Cache_Area_Secondary': '@asset_root/{Task}/cache', 'Asset_Cache_Work_Area': '@Asset_Cache_Area/wip', 'Asset_Cache_Work_Area_Secondary': '@Asset_Cache_Area_Secondary/wip', 'Asset_Cache_Publish_Area': '@Asset_Cache_Area/publish', 'Asset_Cache_Publish_Area_Secondary': '@Asset_Cache_Area_Secondary/publish', 'Asset_MayaScene_ProjectArea': '@asset_root/{Task}/maya', 'Asset_MayaScene_WorkArea': '@Asset_MayaScene_ProjectArea/wip', 'Asset_MayaScene_PublishArea': '@Asset_MayaScene_ProjectArea/publish', 'Asset_MayaScene_Work': '@Asset_MayaScene_WorkArea/@generic_version_name.ma', 'Asset_MayaScene_Snapshot': '@Asset_MayaScene_WorkArea/snapshots/@generic_version_name.{timestamp}.ma', 'Asset_MayaScene_Publish': '@Asset_MayaScene_PublishArea/@generic_version_name.ma', 'Asset_MayaScene_PublishSpecial': '@Asset_MayaScene_PublishArea/{name}-{Task}-{variant}-{special_version}.ma', 'Asset_MayaRender_Work_Generic_Name': '@Asset_Image_WorkArea/@generic_image_dirname', 'Asset_MayaRender_Work_Layer': '@Asset_MayaRender_Work_Generic_Name/{render_layer}', 'Asset_MayaRender_Work_Aov': '@Asset_MayaRender_Work_Layer/{render_aov}', 'Asset_MayaRender_Work_Sequence': '@Asset_MayaRender_Work_Aov/@generic_version_name-{render_layer}-{render_aov}-{colorspace}.{SEQ}.{image_ext}', 'Asset_MayaRender_Publish_Generic_Name': '@Asset_Image_PublishArea/@generic_image_dirname', 'Asset_MayaRender_Publish_Layer': '@Asset_MayaRender_Publish_Generic_Name/{render_layer}', 'Asset_MayaRender_Publish_Aov': '@Asset_MayaRender_Publish_Layer/{render_aov}', 'Asset_MayaRender_Publish_Sequence': '@Asset_MayaRender_Publish_Aov/@generic_version_name-{render_layer}-{render_aov}-{colorspace}.{SEQ}.{image_ext}', 'Asset_MayaBlast_Work_Sequence': '@Asset_Image_WorkArea/@generic_version_name-blast-{colorspace}/{camera}/@generic_version_name_colorspace-{camera}.{SEQ}.{image_ext}', 'Asset_MayaBlast_Publish_Sequence': '@Asset_Image_PublishArea/generic_version_name-blast-{colorspace}/{camera}/@generic_version_name_colorspace-{camera}.{SEQ}.{image_ext}', 'Asset_AlembicCache_Work_File': '@Asset_Cache_Work_Area/abc/@generic_cache_version_name-{tool}/@generic_cache_version_name.abc', 'Asset_AlembicCache_Work_File_Secondary': '@Asset_Cache_Work_Area_Secondary/abc/@generic_cache_version_name-{tool}/@generic_cache_version_name.abc', 'Asset_AlembicCache_Publish_File': '@Asset_Cache_Publish_Area/abc/@generic_cache_version_name-{tool}/@generic_cache_version_name.abc', 'Asset_AlembicCache_Publish_File_Secondary': '@Asset_Cache_Publish_Area_Secondary/abc/@generic_cache_version_name-{tool}/@generic_cache_version_name.abc', 'Asset_YetiCache_Work_File': '@Asset_Cache_Work_Area/fur/@generic_cache_version_name-maya/@generic_cache_version_name.{SEQ}.fur', 'Asset_YetiCache_Publish_File': '@Asset_Cache_Publish_Area/fur/@generic_cache_version_name-maya/@generic_cache_version_name.{SEQ}.fur', 'Asset_YetiDescription_File': '@asset_root/common/hair_asset_description.json', 'Asset_HoudiniScene_WorkArea': '@asset_root/{Task}/houdini/wip', 'Asset_HoudiniScene_PublishArea': '@asset_root/{Task}/houdini/publish', 'Asset_HoudiniCache_PrivateArea': '@Asset_HoudiniScene_WorkArea/@generic_version_name', 'Asset_HoudiniScene_Work': '@Asset_HoudiniScene_WorkArea/@generic_version_name.hip', 'Asset_HoudiniScene_Snapshot': '@Asset_HoudiniScene_WorkArea/snapshots/@generic_version_name.{timestamp}.hip', 'Asset_HoudiniScene_Publish': '@Asset_HoudiniScene_PublishArea/@generic_version_name.hip', 'Asset_HoudiniScene_PublishSpecial': '@Asset_HoudiniScene_PublishArea/{name}-{Task}-{variant}-{special_version}.hip', 'Asset_HoudiniRender_Work_Generic_Name': '@Asset_Image_WorkArea/@generic_image_dirname_houdini', 'Asset_HoudiniRender_Work_Aov': '@Asset_HoudiniRender_Work_Generic_Name/{render_aov}', 'Asset_HoudiniRender_Work_Sequence': '@Asset_HoudiniRender_Work_Aov/@generic_houdini_version_name-{render_aov}.{HSEQ}.{image_ext}', 'Asset_HoudiniRender_Work_Distributed_Sequence': '@Asset_HoudiniRender_Work_Aov/{distribution_type}_{distribution_index}/@generic_houdini_version_name-{render_aov}.{distribution_type}_{distribution_index}.{HSEQ}.{image_ext}', 'Asset_HoudiniRender_Publish_Generic_Name': '@Asset_Image_PublishArea/@generic_image_dirname_houdini', 'Asset_HoudiniRender_Publish_Aov': '@Asset_HoudiniRender_Publish_Generic_Name/{render_aov}', 'Asset_HoudiniRender_Publish_Sequence': '@Asset_HoudiniRender_Publish_Aov/@generic_houdini_version_name-{render_aov}.{HSEQ}.{image_ext}', 'Asset_HoudiniRender_Publish_Distributed_Sequence': '@Asset_HoudiniRender_Publish_Aov/{distribution_type}_{distribution_index}/@generic_houdini_version_name-{render_aov}.{distribution_type}_{distribution_index}.{HSEQ}.{image_ext}', 'Asset_HoudiniCache_Work_Sequence': '@Asset_Cache_Work_Area_Secondary/{cache_type_houdini}/@generic_houdini_version_name-houdini/@generic_houdini_version_name.{HSEQ}.{ext_cache_houdini}', 'Asset_HoudiniCache_Work_File': '@Asset_Cache_Work_Area_Secondary/{cache_type_houdini}/@generic_houdini_version_name-houdini/@generic_houdini_version_name.{ext_cache_houdini}', 'Asset_HoudiniCache_Work_Distributed_Sequence': '@Asset_Cache_Work_Area_Secondary/{cache_type_houdini}/@generic_houdini_version_name-houdini/{distribution_type}_{distribution_index}/@generic_houdini_version_name.{distribution_type}_{distribution_index}.{HSEQ}.{ext_cache_houdini}', 'Asset_HoudiniCache_Work_Distributed_File': '@Asset_Cache_Work_Area_Secondary/{cache_type_houdini}/@generic_houdini_version_name-houdini/{distribution_type}_{distribution_index}/@generic_houdini_version_name.{distribution_type}_{distribution_index}.{ext_cache_houdini}', 'Asset_HoudiniCache_Work_Checkpoints_Sequence': '@Asset_Cache_Work_Area_Secondary/{cache_type_houdini}/@generic_houdini_version_name-houdini/sim/@generic_houdini_version_name.@HSIMSEQ.sim', 'Asset_HoudiniCache_Private_Sequence': '@Asset_HoudiniCache_PrivateArea/{cache_type_houdini}/@generic_houdini_version_name/@generic_houdini_version_name.{HSEQ}.{ext_cache_houdini}', 'Asset_HoudiniCache_Private_File': '@Asset_HoudiniCache_PrivateArea/{cache_type_houdini}/@generic_houdini_version_name/@generic_houdini_version_name.{ext_cache_houdini}', 'Asset_HoudiniCache_Private_Distributed_Sequence': '@Asset_HoudiniCache_PrivateArea/{cache_type_houdini}/@generic_houdini_version_name/{distribution_type}_{distribution_index}/@generic_houdini_version_name.{distribution_type}_{distribution_index}.{HSEQ}.{ext_cache_houdini}', 'Asset_HoudiniCache_Private_Distributed_File': '@Asset_HoudiniCache_PrivateArea/{cache_type_houdini}/@generic_houdini_version_name/{distribution_type}_{distribution_index}/@generic_houdini_version_name.{distribution_type}_{distribution_index}.{ext_cache_houdini}', 'Asset_HoudiniCache_Private_Checkpoints_Sequence': '@Asset_HoudiniCache_PrivateArea/{cache_type_houdini}/@generic_houdini_version_name/sim/@generic_houdini_version_name.@HSIMSEQ.sim', 'Asset_HoudiniCache_Publish_Sequence': '@Asset_Cache_Publish_Area_Secondary/{cache_type_houdini}/@generic_houdini_version_name-houdini/@generic_houdini_version_name.{HSEQ}.{ext_cache_houdini}', 'Asset_HoudiniCache_Publish_File': '@Asset_Cache_Publish_Area_Secondary/{cache_type_houdini}/@generic_houdini_version_name-houdini/@generic_houdini_version_name.{ext_cache_houdini}', 'Asset_HoudiniCache_Publish_Distributed_Sequence': '@Asset_Cache_Publish_Area_Secondary/{cache_type_houdini}/@generic_houdini_version_name-houdini/{distribution_type}_{distribution_index}/@generic_houdini_version_name.{distribution_type}_{distribution_index}.{HSEQ}.{ext_cache_houdini}', 'Asset_HoudiniCache_Publish_Distributed_File': '@Asset_Cache_Publish_Area_Secondary/{cache_type_houdini}/@generic_houdini_version_name-houdini/{distribution_type}_{distribution_index}/@generic_houdini_version_name.{distribution_type}_{distribution_index}.{ext_cache_houdini}', 'Asset_HoudiniFlip_Work_Generic_Name': '@Asset_Image_WorkArea/@generic_version_name-flip', 'Asset_HoudiniFlip_Work_Camera': '@Asset_HoudiniFlip_Work_Generic_Name/{camera}', 'Asset_HoudiniFlip_Work_Sequence': '@Asset_HoudiniFlip_Work_Camera/@generic_version_name-{camera}.{HSEQ}.{image_ext}', 'Asset_HoudiniFlip_Publish_Generic_Name': '@Asset_Image_PublishArea/@generic_version_name-flip', 'Asset_HoudiniFlip_Publish_Camera': '@Asset_HoudiniFlip_Publish_Generic_Name/{camera}', 'Asset_HoudiniFlip_Publish_Sequence': '@Asset_HoudiniFlip_Publish_Camera/@generic_version_name-{camera}.{HSEQ}.{image_ext}', 'Asset_ClarisseScene_ProjectArea': '@asset_root/{Task}/clarisse', 'Asset_ClarisseScene_WorkArea': '@Asset_ClarisseScene_ProjectArea/wip', 'Asset_ClarisseScene_Work': '@Asset_ClarisseScene_WorkArea/@generic_version_name.project', 'Asset_ClarisseScene_Snapshot': '@Asset_ClarisseScene_WorkArea/snapshots/@generic_version_name.{timestamp}.project', 'Asset_ClarisseScene_PublishArea': '@Asset_ClarisseScene_ProjectArea/publish', 'Asset_ClarisseScene_Publish': '@Asset_ClarisseScene_PublishArea/@generic_version_name.project', 'Asset_ClarisseScene_PublishSpecial': '@Asset_ClarisseScene_PublishArea/{name}-{Task}-{variant}-{special_version}.project', 'Asset_ClarisseRender_Work_Generic_Name': '@Asset_Image_WorkArea/@generic_version_name-clarisse', 'Asset_ClarisseRender_Work_Image': '@Asset_ClarisseRender_Work_Generic_Name/{clarisse_image}', 'Asset_ClarisseRender_Work_Layer': '@Asset_ClarisseRender_Work_Image/{clarisse_layer}', 'Asset_ClarisseRender_Work_Sequence': '@Asset_ClarisseRender_Work_Layer/@generic_version_name-{clarisse_image}-{clarisse_layer}-{colorspace}.{SEQ}.{ext_render_clarisse}', 'Asset_ClarisseRender_Publish_Generic_Name': '@Asset_Image_PublishArea/@generic_version_name-clarisse', 'Asset_ClarisseRender_Publish_Image': '@Asset_ClarisseRender_Publish_Generic_Name/{clarisse_image}', 'Asset_ClarisseRender_Publish_Layer': '@Asset_ClarisseRender_Publish_Image/{clarisse_layer}', 'Asset_ClarisseRender_Publish_Sequence': '@Asset_ClarisseRender_Publish_Layer/@generic_version_name-{clarisse_image}-{clarisse_layer}-{colorspace}.{SEQ}.{ext_render_clarisse}', 'Asset_C4dScene_ProjectArea': '@asset_root/{Task}/c4d', 'Asset_C4dScene_WorkArea': '@Asset_C4dScene_ProjectArea/wip', 'Asset_C4dScene_Work': '@Asset_C4dScene_WorkArea/@generic_version_name.c4d', 'Asset_C4dScene_PublishArea': '@Asset_C4dScene_ProjectArea/publish', 'Asset_C4dScene_Publish': '@Asset_C4dScene_PublishArea/@generic_version_name.c4d', 'Asset_C4dScene_PublishSpecial': '@Asset_C4dScene_PublishArea/{name}-{Task}-{variant}-{special_version}.c4d', 'Asset_C4dRender_Work_Generic_Name': '@Asset_Image_WorkArea/@generic_image_dirname_c4d', 'Asset_C4dRender_Work_Aov': '@Asset_C4dRender_Work_Generic_Name/{render_aov}', 'Asset_C4dRender_Work_Sequence': '@Asset_C4dRender_Work_Aov/@generic_version_name_c4d.{SEQ}.{ext_render_c4d}', 'Asset_C4dRender_Publish_Generic_Name': '@Asset_Image_PublishArea/@generic_image_dirname_c4d', 'Asset_C4dRender_Publish_Aov': '@Asset_C4dRender_Publish_Generic_Name/{render_aov}', 'Asset_C4dRender_Publish_Sequence': '@Asset_C4dRender_Publish_Aov/@generic_version_name_c4d.{SEQ}.{ext_render_c4d}', 'Asset_NukeScene_WorkArea': '@asset_root/{Task}/nuke/wip', 'Asset_NukeScene_PublishArea': '@asset_root/{Task}/nuke/publish', 'nuke_asset_render_movie': '@asset_root/common/review/{name}_{Task}_{output}_v{version}.mov', 'Asset_NukeScene_Work': '@Asset_NukeScene_WorkArea/@generic_version_name.nk', 'nuke_asset_work_render': '@Asset_NukeScene_WorkArea/renders/@generic_version_name_r{render_iteration}.nk', 'Asset_NukeScene_Snapshot': '@Asset_NukeScene_WorkArea/@generic_version_name.{timestamp}.nk', 'Asset_NukeScene_Publish': '@Asset_NukeScene_PublishArea/@generic_version_name.nk', 'Asset_NukeScene_PublishSpecial': '@Asset_NukeScene_PublishArea/{name}-{Task}-{variant}-{special_version}.nk', 'Asset_NukeRender_Work_Generic_Name': '@Asset_Image_WorkArea/@generic_image_dirname_nuke', 'Asset_NukeRender_Work_Sequence': '@Asset_NukeRender_Work_Generic_Name/@nuke_image_name.{SEQ}.{ext_render_nuke}', 'Asset_NukeRender_Publish_Generic_Name': '@Asset_Image_PublishArea/@generic_image_dirname_nuke', 'Asset_NukeRender_Publish_Sequence': '@Asset_NukeRender_Publish_Generic_Name/@nuke_image_name.{SEQ}.{ext_render_nuke}', 'Asset_NukeRender_Publish_Movie': '@Asset_NukeRender_Publish_Generic_Name.mov', 'Asset_NukeProxy_Work_Sequence': '@Asset_Image_WorkArea/@nuke_image_name-pxy/@nuke_image_name.{SEQ}.{ext_proxy}', 'Asset_Element_NukeRender_Root': '@asset_task_root/@Element_NukeRender_Root', 'Asset_Element_NukeRender_Generic_Name': '@asset_task_root/@Element_NukeRender_Generic_Name', 'Asset_Element_NukeRender_Sequence': '@Asset_Element_NukeRender_Generic_Name/@nuke_image_name.{SEQ}.{ext_render_nuke}', 'Asset_PhotoshopScene_ProjectArea': '@asset_root/{Task}/photoshop', 'Asset_PhotoshopScene_WorkArea': '@Asset_PhotoshopScene_ProjectArea/wip', 'Asset_PhotoshopScene_Work': '@Asset_PhotoshopScene_WorkArea/@generic_version_name.{ext_scene_photoshop}', 'Asset_PhotoshopScene_PublishArea': '@Asset_PhotoshopScene_ProjectArea/publish', 'Asset_PhotoshopScene_Publish': '@Asset_PhotoshopScene_PublishArea/@generic_version_name.{ext_scene_photoshop}', 'Asset_PhotoshopScene_PublishSpecial': '@Asset_PhotoshopScene_PublishArea/{name}-{Task}-{variant}-{special_version}.{ext_scene_photoshop}', 'Asset_PhotoshopRender_Work_Image': '@Asset_Image_WorkArea/@photoshop_image_name.{extension}', 'Asset_PhotoshopRender_Publish_Image': '@Asset_Image_PublishArea/@photoshop_image_name.{extension}', 'Asset_HarmonyRender_Work_Image': '@Asset_Image_WorkArea/@harmony_image_name-{image_ext}/@harmony_image_name.{SEQ}.{image_ext}', 'Asset_HarmonyRender_Publish_Image': '@Asset_Image_PublishArea/@harmony_image_name-{image_ext}/@harmony_image_name.{SEQ}.{image_ext}', 'Asset_AfterfxRender_Work_Generic_Name': '@Asset_Image_WorkArea/@generic_image_dirname_afterfx', 'Asset_AfterfxRender_Work_Sequence': '@Asset_AfterfxRender_Work_Generic_Name/@afterfx_image_name.{SEQ}.{ext_render_afterfx}', 'Asset_BlenderRender_Work_Generic_Name': '@Asset_Image_WorkArea/@generic_image_dirname_blender', 'Asset_BlenderRender_Work_Sequence': '@Asset_BlenderRender_Work_Generic_Name/@blender_image_name.{SEQ}.{ext_render_blender}'}";
	std::string strs = "{'generic_version_name': '{name}-{Task}-{variant}-v{version}', 'generic_houdini_version_name': '{name}-{Task}-{variant}-{extra_variant}-v{version}', 'generic_cache_version_name': '{name}-{Task}-{variant}-{cache_variant}-v{version}', 'generic_version_name_colorspace': '{name}-{Task}-{variant}-v{version}-{colorspace}', 'generic_version_name_c4d': '{name}-{Task}-{variant}-v{version}-{image_variant}', 'generic_golaem_cache_version_name': '{name}-{Task}-{variant}[-{extra_variant}]-v{version}', 'generic_image_dirname': '@generic_version_name-{render_source}', 'generic_image_dirname_houdini': '@generic_houdini_version_name-{houdini_render_source}', 'generic_image_dirname_nuke': '{name}-{Task}-{variant}-{render_source}-{write_node}-v{version}-{colorspace}-{ext_render_nuke}', 'generic_image_dirname_flame': '{name}-{Task}-{variant}-{flame_render_source}-{write_node}-v{version}-{colorspace}-{ext_render_flame}', 'generic_image_dirname_c4d': '@generic_version_name_c4d-c4dtoa', 'generic_image_dirname_afterfx': '@afterfx_image_name-{ext_render_afterfx}', 'generic_image_dirname_blender': '@blender_image_name-{ext_render_blender}', 'nuke_image_name': '{name}-{Task}-{variant}-{render_source}-{write_node}-v{version}-{colorspace}', 'flame_image_name': '{name}-{Task}-{variant}-{flame_render_source}-{write_node}-v{version}-{colorspace}', 'photoshop_image_name': '{name}-{Task}-{variant}-{photoshop_render_source}-{write_node}-v{version}-{colorspace}', 'harmony_image_name': '{name}-{Task}-{variant}-{harmony_render_source}-{write_node}-v{version}-{colorspace}', 'afterfx_image_name': '{name}-{Task}-{variant}-{afterfx_render_source}-{write_node}-v{version}-{colorspace}', 'blender_image_name': '{name}-{Task}-{variant}-{blender_render_source}-{write_node}-v{version}-{colorspace}', 'nuke_shot_version_name': '@generic_version_name.{iteration}', 'hiero_version': '{version}', 'client_shot_name': '{shot_client_review_name}', 'HSIMSEQ': '$SF4'}";

	std::map<std::string, std::string> strsDict;
	std::map<std::string, std::string> pathsDict;
	std::map<std::string, std::map<std::string, std::string>> keysDict;

	std::string root = "D:\\Desk\\python\\Projects\\Project3";
	// std::string test_image = "D:\\Desk\\python\\Projects\\sequence\\sh\\sh_010\\cmp\\image\\wip\\sh_010-cmp-caca-nk-out-v0001-linear-exr\\sh_010-cmp-caca-nk-out-v0001-linear.####.exr";

	std::string zz = "D:/Desk/python/Tank/tests/project/sequence/test/test_010/cmp/nuke/wip/test_010-cmp-base-v001.nk";
    // std::string test_image = "D:\\Desk\\python\\Projects\\sequence\\sh\\sh_010\\cmp\\nuke\\wip\\010-cmp-base-v0010.nk";
    // std::string test_image = "D:\\Desk\\python\\Projects\\sequence\\sh\\sh_010\\cmp\\nuke\\wip\\010-cmp-base-v010.nk";

    // std::string static_parse = "/sequence/|/|/|/image/wip/|-|-|-|-v|-|-|/|-|-|-|-|-v|-|\\.|\\.|-";
	// std::string definition_splited[] = {
    //     "%(name)-%(Task)-%(variant)-%(render_source)-%(write_node)-v%(version)-%(colorspace).%(SEQ).%(ext_render_nuke)"
    // };

    // std::string path_splited[] = {
    //     "sh_010-cmp-caca-nk-out-v0001-linear.####.exr"
    // };

    // std::regex rgx(static_parse);
    // std::sregex_token_iterator iterDefin(definition_splited[0].begin(), definition_splited[0].end(), rgx, -1);
    // std::sregex_token_iterator iterPath(path_splited[0].begin(), path_splited[0].end(), rgx, -1);
    // std::vector<std::string> token_def(iterDefin, {});
    // std::vector<std::string> tokens_val(iterPath, {});

    // for (int i=0; i<token_def.size(); i++) {
    //     std::cout << "token  " << token_def[i] << " value "<< tokens_val[i] << std::endl;
    // }
	// return 1;

	
	std::map<std::string, std::string> fields;
	fields["Shot"] = "sh_010";
	fields["Task"] = "cmp";
	fields["version"] = "1";
	fields["Sequence"] = "sh";
	fields["render_source"] = "nk";
	fields["SEQ"] = "####";
	fields["write_node"] = "out";
	fields["variant"] = "base";
	fields["colorspace"] = "aces";
	fields["name"] = "sh_010";
	fields["project_resolution"] = "19201080";
	fields["path_additional"] = "caca";
	fields["ext_render_nuke"] = "exr";
	fields["playlist_name"] = "TEST";

	// #if defined(_WIN32)
	// std::cout << "Wubdiw" << std::endl;
	// #elif defined(__linux__)
	// std::cout << "Elsew" << std::endl;
	// #elif defined(__APPLE__)

	// std::cout << "Applw" << std::endl;
	// #endif
	// pathsDict = generatePathsDictionnaryFromString(paths);
	// keysDict  = generateKeysDictionnaryFromString(config);
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
	// // std::cout << " Get Keys " << std::endl;
	// std::cout << "" << std::endl;
	


	Tank tank_test(config, root);
	// std::map<std::string, TemplatePath> templates =  tank_test.getTemplates();

	for(const auto& key : tank_test.getAllKeys()) {

		const std::string& cle = key.first;
		const std::string& valeur = key.second->getDefault();
		// const std::string& value = key.second->getValue();
		std::cout << cle << " : " << valeur << " : " << std::endl;
	}

	// std::cout << "" << std::endl;
	// for (const auto& paire : templates) {
	// 	const std::string& cle = paire.first;
    //     const std::string& valeur = paire.second.getDefinition();
	// 	std::cout << cle << " : " << valeur << std::endl;
	// }
	// return 1;

	// std::cout << "" << std::endl;
	// TemplatePath nuke_tpl = templates["Shot_NukeRender_Work_Sequence"];
	// TemplatePath nuke_tpl = templates["shot_task_root"];
	// std::cout << "definition" << std::endl;
	// std::cout << nuke_tpl.getName() << std::endl;
	// std::cout << nuke_tpl.getDefinition() << std::endl;
	// std::cout << "" << std::endl;
	// nuke_tpl.createFile(fields);
	// // std::vector<std::string> test = nuke_tpl.getOrderedKeys();
	// // for(int i=0; i<test.size(); i++){	
	// // 	std::cout << test[i] << std::endl;
	// // }
	// std::cout << "" << std::endl;
	// std::cout << "testpath" << std::endl;
	// std::string testpath = nuke_tpl.apply_fields(fields);
	// std::cout << testpath << std::endl;

	// std::cout << "" << std::endl;
	// std::vector<std::string> test = nuke_tpl.missingKeys(fields);
	// std::cout << "Missing keys" << std::endl;
	// for(int i=0; i<test.size(); i++){
	// 	std::cout << test[i] << std::endl;
	// }
	
	// TemplatePath delviery = templates["Shot_NukeScene_WorkArea"];
	// TemplatePath delviery = templates["Shot_NukeRender_Work_Sequence"];
	// TemplatePath delviery = templates["Quicktime_Delivery"];
	// TemplatePath sequence_tpl = templates["Shot_NukeRender_Work_Sequence"];
	// TemplatePath nuke_tpl = templates["shot_task_root"];
	// std::cout << "definition" << std::endl;
	// std::cout << sequence_tpl.getName() << std::endl;
	// std::cout << sequence_tpl.getDefinition() << std::endl;
	// std::cout << splitPath(sequence_tpl.getDefinition()).size() << std::endl;
	// std::cout << "" << std::endl;

	// std::string test_image = "D:\\Desk\\python\\Projects\\sequence\\sh\\sh_010\\cmp\\image\\wip\\sh_010-cmp-caca-nk-out-v0001-linear-exr\\sh_010-cmp-caca-nk-out-v0001-linear.####.exr";
	// std::string test_image2 = "D:\\Desk\\python\\Projects\\sequence\\sh\\sh_010\\cmp\\image\\wip\\sh_010-cmp-caca-nk-out-v0001-linear-exr";

	// std::cout << "" << std::endl;
	// delviery.createFile(fields);
	// std::cout << delviery.getName() << std::endl;
	// std::cout << delviery.getDefinition() << std::endl;
	// std::cout << delviery.getDefinitionVariants()[0] << std::endl;
	// std::cout << delviery.apply_fields(fields) << std::endl;
	// std::cout << "" << std::endl;
	// std::cout << delviery.getDefinitionVariants().size() << std::endl;
	// for (const std::string& variant : delviery.getDefinitionVariants()) {
    //     std::cout << "variant   " << variant << std::endl;
    // }
	// std::cout << "" << std::endl;
	// std::cout << "" << std::endl;
	// std::cout << sequence_tpl.getName() << std::endl;
	// std::cout << sequence_tpl.getDefinition() << std::endl;
	// std::cout << "" << std::endl;
	// std::cout << sequence_tpl.getDefinitionVariants().size() << std::endl;
	// for (const std::string& variant : sequence_tpl.getDefinitionVariants()) {
    //     std::cout << variant << std::endl;
    // }
	// std::cout << "" << std::endl;


    // std::sregex_token_iterator iter(text.begin(), text.end(), pattern, -1);
	// std::sregex_token_iterator end;
	// std::vector<std::string> tokens;
    // for (; iter != end; ++iter) {
    //     tokens.push_back(iter->str());
    // }

    // for (const std::string& token : tokens) {
    //     std::cout << "token  " << token << std::endl;
    // }

	// std::cout << "" << std::endl;
	// std::string path = "D:\\Desk\\python\\Projects\\sequence\\sh\\sh_010";
	// TemplatePath nuke_tpl = tank_test.templateFromPath(test_image);
	// std::cout << "" << std::endl;
	// std::map<std::string, std::string> get_fields = nuke_tpl.getFields(test_image);
	// std::cout << "" << std::endl;
	// std::cout << "Get Fields" << std::endl;
	// if(get_fields.size() >0){
	// 	std::cout << "Path found !!!" << std::endl;
	// }
	// for (const auto& paire : get_fields) {
	// 	const std::string& cle = paire.first;
    //     const std::string& valeur = paire.second;
	// 	std::cout << cle << " : " << valeur << std::endl;
	// }

	// std::cout << "D:\\Desk\\python\\Tank\\tests\\project" << std::endl;
	// std::cout << pattern_test << std::endl;
	// std::vector<std::string> abspathsTest2 = listFilesFromPathPattern("D:\\Desk\\python\\Tank\\tests\\project", pattern_test);

	// {'Sequence': 'sh', 'Shot': 'sh_010', 'Task': 'cmp', 'colorspace': 'linear', 'ext_render_nuke': 'exr', 'name': 'sh_010', 'render_source': 'nk', 'variant': 'base', 'write_node': 'out'}
	std::string path_image = "D:\\Desk\\python\\Projects\\sequence\\sh\\sh_010\\cmp\\image\\wip\\sh_010-cmp-base-nk-out-v001-linear-exr\\sh_010-cmp-base-nk-out-v001-linear.1010.exr";
	// std::string path_image = "D:\\Desk\\python\\Projects\\sequence\\sh\\sh_010\\cmp\\image\\wip\\sh_010-cmp-base-nk-out-v001-linear-exr\\sh_010-cmp-base-nk-out-v001-linear.####.exr";
	std::string master = "D:\\Desk\\python\\Projects\\sequence\\sh\\sh_010\\common\\footage\\sh_010-src-master01-v001-aces-exr\\sh_010-src-master01-v001-aces.1001.exr";
	std::string master2 = "D:\\Desk\\python\\Projects\\sequence\\sh\\sh_010";
	std::string master_seq = "D:\\Desk\\python\\Projects\\sequence\\sh\\sh_010\\common\\footage\\sh_010-src-master01-v001-aces-exr";
	// std::string master_seq = "D:/Desk/python/Projects/sequence/sh/sh_010/common/footage/sh_010-src-master01-v001-aces-exr";


	// std::cout << "" << std::endl;
	// std::vector<std::string> abspathsTest = tank_test.getAbstractPathsFromTemplate(sequence_tpl, fields);
	// std::cout << "size" 	<< abspathsTest.size() << std::endl;
	// for(int i=0; i<abspathsTest.size(); i++){
	// 	std::cout << "match  " << abspathsTest[i] << std::endl;
	// }

	// std::cout << "" << std::endl;
	// std::string testpath = sequence_tpl.apply_fields(fields);
	// std::cout << testpath << std::endl;
	
	// std::cout << "###########################" <<std::endl;
	// TemplatePath aTesty = tank_test.templateFromPath(master_seq);
	// std::cout << master << std::endl;
	// std::cout << aTesty.getName() << std::endl;
	// std::cout << aTesty.getDefinition() << std::endl;
	// std::cout << aTesty.getOrderedKeys() << std::endl;

	// std::cout << "" << std::endl;
	// TemplatePath nuke_tpl = templates["Shot_NukeScene_Work"];
	// std::cout << "definition" << std::endl;
	// std::cout << nuke_tpl.getDefinition() << std::endl;

	// std::vector<std::string> etfiel = aTesty.getStaticTokens();
	// for (int i=0; i<etfiel.size(); i++) {
    //     std::cout << etfiel[i] << std::endl ;
    // }
	// std::cout << " " <<std::endl;
	// for (const auto& paire : aTesty.getFields(_path)) {
	// 	const std::string& cle = paire.first;
    //     const std::string& valeur = paire.second;
	// 	std::cout << cle << " : " << valeur << std::endl;
	// }
	// TemplatePath aTestya = tank_test.templateFromPath(path_image);
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