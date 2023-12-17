

#include "editor_import_gltf_mdr.h"

String EditorImportGLTFMdr::get_importer_name() const {
	return "gltf_mdr";
}

String EditorImportGLTFMdr::get_visible_name() const {
	return "GLTF MDR";
}

void EditorImportGLTFMdr::get_recognized_extensions(List<String> *p_extensions) const {
	p_extensions->push_back("gltf");
	p_extensions->push_back("glb");
}

String EditorImportGLTFMdr::get_save_extension() const {
	return "res";
}

String EditorImportGLTFMdr::get_resource_type() const {
	return "MeshDataResource";
}

float EditorImportGLTFMdr::get_priority() const {
	return 1.0;
}

int EditorImportGLTFMdr::get_preset_count() const {
	return 0;
}

String EditorImportGLTFMdr::get_preset_name(int p_idx) const {
	return "";
}

Error EditorImportGLTFMdr::import(const String &p_source_file, const String &p_save_path, const RBMap<StringName, Variant> &p_options, List<String> *r_platform_variants, List<String> *r_gen_files, Variant *r_metadata) {
	//MeshDataResource::ColliderType collider_type = static_cast<MeshDataResource::ColliderType>(static_cast<int>(p_options["collider_type"]));

	Error erri;

	Node *n = _importer->import_scene(p_source_file, 0, 15, 0, nullptr, &erri);

	ERR_FAIL_COND_V(!n, Error::ERR_PARSE_ERROR);

	if (erri != Error::OK) {
		return erri;
	}

	Error err = process_node(n, p_source_file, p_save_path, p_options, r_platform_variants, r_gen_files, r_metadata);

	n->queue_delete();
	return err;
}

EditorImportGLTFMdr::EditorImportGLTFMdr() {
	_importer.instance();
}

EditorImportGLTFMdr::~EditorImportGLTFMdr() {
	_importer.unref();
}
