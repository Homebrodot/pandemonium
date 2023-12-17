#ifndef MM_BRICKS_H
#define MM_BRICKS_H

/*************************************************************************/
/*  bricks.h                                                             */
/*************************************************************************/
/*                         This file is part of:                         */
/*                          PANDEMONIUM ENGINE                           */
/*             https://github.com/Relintai/pandemonium_engine            */
/*************************************************************************/
/* Copyright (c) 2022-present Péter Magyar.                              */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "../mm_node.h"
#include "../mm_node_universal_property.h"

class MMBricks : public MMNode {
	GDCLASS(MMBricks, MMNode);

public:
	Ref<MMNodeUniversalProperty> get_out_bricks_pattern();
	void set_out_bricks_pattern(const Ref<MMNodeUniversalProperty> &val);

	Ref<MMNodeUniversalProperty> get_out_random_color();
	void set_out_random_color(const Ref<MMNodeUniversalProperty> &val);

	Ref<MMNodeUniversalProperty> get_out_position_x();
	void set_out_position_x(const Ref<MMNodeUniversalProperty> &val);

	Ref<MMNodeUniversalProperty> get_out_position_y();
	void set_out_position_y(const Ref<MMNodeUniversalProperty> &val);

	Ref<MMNodeUniversalProperty> get_out_brick_uv();
	void set_out_brick_uv(const Ref<MMNodeUniversalProperty> &val);

	Ref<MMNodeUniversalProperty> get_out_corner_uv();
	void set_out_corner_uv(const Ref<MMNodeUniversalProperty> &val);

	Ref<MMNodeUniversalProperty> get_out_direction();
	void set_out_direction(const Ref<MMNodeUniversalProperty> &val);

	int get_type() const;
	void set_type(const int val);

	int get_repeat() const;
	void set_repeat(const int val);

	Vector2 get_col_row();
	void set_col_row(const Vector2 &val);

	float get_offset() const;
	void set_offset(const float val);

	Ref<MMNodeUniversalProperty> get_mortar();
	void set_mortar(const Ref<MMNodeUniversalProperty> &val);

	Ref<MMNodeUniversalProperty> get_bevel();
	void set_bevel(const Ref<MMNodeUniversalProperty> &val);

	Ref<MMNodeUniversalProperty> get_roundness();
	void set_roundness(const Ref<MMNodeUniversalProperty> &val);

	float get_corner() const;
	void set_corner(const float val);

	void _init_properties();
	void _register_methods(MMGraphNode *mm_graph_node);
	void _render(const Ref<MMMaterial> &material);
	Color _get_value_for(const Vector2 &uv, const int pseed);

	MMBricks();
	~MMBricks();

protected:
	static void _bind_methods();

	Ref<MMNodeUniversalProperty> out_bricks_pattern;
	Ref<MMNodeUniversalProperty> out_random_color;
	Ref<MMNodeUniversalProperty> out_position_x;
	Ref<MMNodeUniversalProperty> out_position_y;
	Ref<MMNodeUniversalProperty> out_brick_uv;
	Ref<MMNodeUniversalProperty> out_corner_uv;
	Ref<MMNodeUniversalProperty> out_direction;
	//export(int, "Running Bond,Running Bond (2),HerringBone,Basket Weave,Spanish Bond")
	int type;
	int repeat;
	Vector2 col_row;
	float offset;
	Ref<MMNodeUniversalProperty> mortar;
	Ref<MMNodeUniversalProperty> bevel;
	Ref<MMNodeUniversalProperty> roundness;
	float corner;
};

#endif
