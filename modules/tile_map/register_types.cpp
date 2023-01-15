/*
Copyright (c) 2021 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "register_types.h"

#include "tile_map.h"
#include "tile_set.h"

#ifdef TOOLS_ENABLED
#include "tile_map_editor_plugin.h"
#include "tile_set_editor_plugin.h"
#endif

void register_tile_map_types(ModuleRegistrationLevel p_level) {
#ifdef TOOLS_ENABLED
	EditorPlugins::add_by_type<TileMapEditorPlugin>();
	EditorPlugins::add_by_type<TileSetEditorPlugin>();
#endif

	ClassDB::register_class<TileMap>();
	ClassDB::register_class<TileSet>();

#ifndef DISABLE_DEPRECATED
	ClassDB::add_compatibility_class("RTileMap", "TileMap");
	ClassDB::add_compatibility_class("RTileSet", "TileSet");
#endif
}

void unregister_tile_map_types(ModuleRegistrationLevel p_level) {
}
