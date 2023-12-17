#ifndef ADMIN_NODE_H
#define ADMIN_NODE_H

/*************************************************************************/
/*  admin_node.h                                                         */
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

#include "web/http/web_node.h"

#include "core/containers/vector.h"
#include "core/string.h"

class Request;
class FormValidator;

struct AdminSectionLinkInfo {
	String name;
	String link;

	AdminSectionLinkInfo() {
	}

	AdminSectionLinkInfo(const String &p_name, const String &p_link) {
		name = p_name;
		link = p_link;
	}
};

class AdminNode : public WebNode {
	RCPP_OBJECT(AdminNode, WebNode);

public:
	virtual void admin_handle_request_main(Request *request);
	virtual String admin_get_section_name();
	virtual void admin_add_section_links(Vector<AdminSectionLinkInfo> *links);
	virtual bool admin_full_render();

	AdminNode();
	~AdminNode();

protected:
};

#endif