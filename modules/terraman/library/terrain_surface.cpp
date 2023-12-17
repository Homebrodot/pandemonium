

#include "terrain_surface.h"

int TerrainSurface::get_id() const {
	return _id;
}
void TerrainSurface::set_id(const int value) {
	_id = value;
}

Rect2 TerrainSurface::get_rect(const TerrainSurfaceSides side) const {
	return _rects[side];
}
void TerrainSurface::set_rect(const TerrainSurfaceSides side, const Rect2 &rect) {
	_rects[side] = rect;
}

Ref<TerrainLibrary> TerrainSurface::get_library() const {
	return Ref<TerrainLibrary>(_library);
}

void TerrainSurface::set_library(Ref<TerrainLibrary> library) {
	_library = (*library);
}

_FORCE_INLINE_ Vector2 TerrainSurface::transform_uv(const TerrainSurfaceSides p_side, const Vector2 &p_uv) const {
	Vector2 uv = p_uv;

	Rect2 r = _rects[p_side];

	uv.x *= r.size.x;
	uv.y *= r.size.y;
	uv.x += r.position.x;
	uv.y += r.position.y;

	return uv;
}

_FORCE_INLINE_ Vector2 TerrainSurface::transform_uv_scaled(const TerrainSurfaceSides p_side, const Vector2 &p_uv, const int p_current_x, const int p_current_y, const int p_max) const {
	Vector2 uv = p_uv;

	Rect2 r = _rects[p_side];

	float sizex = r.size.x / static_cast<float>(p_max);
	float sizey = r.size.y / static_cast<float>(p_max);

	uv.x *= sizex;
	uv.y *= sizey;

	uv.x += r.position.x + sizex * p_current_x;
	uv.y += r.position.y + sizey * p_current_y;

	return uv;
}

void TerrainSurface::refresh_rects() {
}

TerrainSurface::TerrainSurface() {
	_id = 0;
	_mesher_index = 0;
	_transparent = false;
	_liquid = false;
	_library = NULL;
}

TerrainSurface::~TerrainSurface() {
	_library = NULL;
}

void TerrainSurface::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &TerrainSurface::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &TerrainSurface::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "voxel_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_rect", "side"), &TerrainSurface::get_rect);
	ClassDB::bind_method(D_METHOD("set_rect", "side", "rect"), &TerrainSurface::set_rect);

	ClassDB::bind_method(D_METHOD("transform_uv", "side", "uv"), &TerrainSurface::transform_uv);
	ClassDB::bind_method(D_METHOD("transform_uv_scaled", "side", "uv", "p_current_x", "p_current_y", "max"), &TerrainSurface::transform_uv_scaled);

	ClassDB::bind_method(D_METHOD("refresh_rects"), &TerrainSurface::refresh_rects);

	BIND_ENUM_CONSTANT(TERRAIN_SIDE_TOP);
	BIND_ENUM_CONSTANT(TERRAIN_SIDE_BOTTOM);
	BIND_ENUM_CONSTANT(TERRAIN_SIDE_SIDE);

	BIND_CONSTANT(TERRAIN_SIDES_COUNT);
}
