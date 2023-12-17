

#include "ground_clutter.h"

#include "modules/modules_enabled.gen.h"

#ifdef MODULE_VOXELMAN_ENABLED
#include "../../voxelman/world/voxel_chunk.h"

bool GroundClutter::should_spawn(Ref<VoxelChunk> chunk, int x, int y, int z) {
	if (has_method("_should_spawn"))
		return call("_should_spawn", chunk, x, y, z);

	return false;
}

void GroundClutter::add_meshes_to(Ref<VoxelMesher> mesher, Ref<VoxelChunk> chunk, int x, int y, int z) {
	if (has_method("_add_meshes_to"))
		call("_add_meshes_to", mesher, chunk, x, y, z);
}
#endif

#ifdef MODULE_TEXTURE_PACKER_ENABLED
void GroundClutter::add_textures_to(Ref<TexturePacker> packer) {
	if (has_method("_add_textures_to"))
		call("_add_textures_to", packer);
}
#endif

GroundClutter::GroundClutter() {
}

GroundClutter::~GroundClutter() {
}

void GroundClutter::_bind_methods() {
#ifdef MODULE_TEXTURE_PACKER_ENABLED
	BIND_VMETHOD(MethodInfo("_add_textures_to", PropertyInfo(Variant::OBJECT, "packer", PROPERTY_HINT_RESOURCE_TYPE, "TexturePacker")));

	ClassDB::bind_method(D_METHOD("add_textures_to", "packer"), &GroundClutter::add_textures_to);
#endif

#ifdef MODULE_VOXELMAN_ENABLED
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "should"), "_should_spawn", PropertyInfo(Variant::OBJECT, "chunk", PROPERTY_HINT_RESOURCE_TYPE, "VoxelChunk"), PropertyInfo(Variant::INT, "x"), PropertyInfo(Variant::INT, "y"), PropertyInfo(Variant::INT, "z")));
	BIND_VMETHOD(MethodInfo("_add_meshes_to", PropertyInfo(Variant::OBJECT, "mesher", PROPERTY_HINT_RESOURCE_TYPE, "VoxelMesher"), PropertyInfo(Variant::OBJECT, "chunk", PROPERTY_HINT_RESOURCE_TYPE, "VoxelChunk"), PropertyInfo(Variant::INT, "x"), PropertyInfo(Variant::INT, "y"), PropertyInfo(Variant::INT, "z")));

	ClassDB::bind_method(D_METHOD("should_spawn", "chunk", "x", "y", "z"), &GroundClutter::should_spawn);
	ClassDB::bind_method(D_METHOD("add_meshes_to", "mesher", "chunk", "x", "y", "z"), &GroundClutter::add_meshes_to);
#endif
}
