#ifndef LEFT_PANEL_H
#define LEFT_PANEL_H

/*************************************************************************/
/*  left_panel.h                                                         */
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

#include "core/input/input_event.h"
#include "core/string/ustring.h"
#include "core/variant/array.h"

#include "scene/gui/box_container.h"

class ItemList;

class LeftPanel : public VBoxContainer {
	GDCLASS(LeftPanel, VBoxContainer);

public:
	Array get_recents();
	void set_recents(const Array &val);

	Array get_favorites();
	void set_favorites(const Array &val);

	void add_recent(const String &file_path);
	void add_favorite(const String &file_path);

	String my_basename(const String &s);
	void update_lists();

	void _on_FavList_item_activated(const int index);
	void _on_RecentList_item_activated(const int index);
	void _on_FavList_gui_input(const Ref<InputEvent> &event);
	void _on_RecentList_gui_input(const Ref<InputEvent> &event);

	LeftPanel();
	~LeftPanel();

protected:
	static void _bind_methods();

	Array recents;
	Array favorites;

	ItemList *_recent_list;
	ItemList *_fav_list;
};

#endif
