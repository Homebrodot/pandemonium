#ifndef PAINT_PROJECT_PROPERTY_INSPECTOR_H
#define PAINT_PROJECT_PROPERTY_INSPECTOR_H



#include "core/object/object_id.h"
#include "core/object/reference.h"
#include "paint_custom_property_inspector.h"

class GridContainer;
class PaintNode;
class PaintProject;
class HFlowContainer;
class ColorSelectorButton;
class Button;

class PaintProjectPropertyInspector : public PaintCustomPropertyInspector {
	GDCLASS(PaintProjectPropertyInspector, PaintCustomPropertyInspector);

public:
	void add_grid_button(const Color &color, const int color_index);
	void create_grid_buttons();
	void clear_grid_buttons();

	void _set_paint_node(Node *paint_node);

	PaintProjectPropertyInspector();
	~PaintProjectPropertyInspector();

protected:
	void _on_grid_color_button_changed(const Color &color, Node *button);
	void _on_grid_color_button_pressed(Node *button);
	void _on_main_color_changed(const Color &color);
	void _on_main_color_selected();
	void _on_add_color_button_pressed();
	void _on_project_color_changed(const Color &color);
	void _on_project_color_preset_changed();

	void _notification(int p_what);

	static void _bind_methods();

	HFlowContainer *_color_grid;
	ColorSelectorButton *_main_color_button;
	Button *_add_color_button;

	ObjectID _current_paint_node;
	ObjectID _current_paint_project;

	bool _ignore_preset_changed_event;
	bool _ignore_color_event;
};

#endif
