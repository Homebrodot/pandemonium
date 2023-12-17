#ifndef MDR_UV_RECT_VIEW_NODE_H
#define MDR_UV_RECT_VIEW_NODE_H



#include "core/math/color.h"
#include "core/math/rect2.h"
#include "core/containers/pool_vector.h"
#include "core/object/reference.h"

#include "scene/gui/margin_container.h"

class MeshDataResource;

class MDRUVRectViewNode : public MarginContainer {
	GDCLASS(MDRUVRectViewNode, MarginContainer);

public:
	enum DragType {
		DRAG_NONE = 0,
		DRAG_MOVE = 1,
		DRAG_RESIZE_TOP = 1 << 1,
		DRAG_RESIZE_RIGHT = 1 << 2,
		DRAG_RESIZE_BOTTOM = 1 << 3,
		DRAG_RESIZE_LEFT = 1 << 4
	};

	void set_edited_resource(const Ref<MeshDataResource> &mdr, const PoolIntArray &indices);

	void mirror_horizontal();
	void mirror_vertical();
	void rotate_uvs(float amount);

	void set_selected(bool val);

	void set_editor_rect_scale(float rect_scale);
	void set_up_base_rect();

	void re_normalize_uvs();
	void normalize_uvs();
	void apply_uv();
	
	void refresh();

	void _draw();
	void _gui_input(const Ref<InputEvent> &p_event);
	int _drag_hit_test(const Vector2 &pos);

	MDRUVRectViewNode();
	~MDRUVRectViewNode();

protected:
	
	void _notification(int p_what);
	static void _bind_methods();

public:
	bool selected;

	Ref<MeshDataResource> _mdr;
	PoolIntArray _indices;
	PoolVector2Array _uvs;
	Rect2 _base_rect;
	Vector2 _uv_min;
	Vector2 _uv_max;

	Vector2 edited_resource_parent_size;

	Color _edited_resource_rect_border_color;
	Color _edited_resource_rect_color;
	Color _edited_resource_rect_selected_border_color;
	Color _edited_resource_rect_selected_color;
	Color _edited_resource_uv_mesh_color;
	int _editor_rect_border_size;
	Color _edited_resource_font_color;
	String _editor_additional_text;

	int drag_type;
	Vector2 drag_offset;
	Vector2 drag_offset_far;

	float _rect_scale;
};

#endif
