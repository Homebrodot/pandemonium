#ifndef FAST_WFC_UTILS_ARRAY3D_HPP_
#define FAST_WFC_UTILS_ARRAY3D_HPP_

/*************************************************************************/
/*  array_3d.h                                                           */
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

#include "core/containers/vector.h"

template <typename T>
class Array3D {
public:
	int height;
	int width;
	int depth;

	Vector<T> data;

	Array3D() {
		height = 0;
		width = 0;
		depth = 0;
	}

	Array3D(int p_height, int p_width, int p_depth) {
		height = p_height;
		width = p_width;
		depth = p_depth;
		data.resize(width * height * depth);
	}

	Array3D(int p_height, int p_width, int p_depth, T value) {
		height = p_height;
		width = p_width;
		depth = p_depth;
		data.resize(width * height * depth);
		data.fill(value);
	}

	void resize(int p_height, int p_width, int p_depth) {
		height = p_height;
		width = p_width;
		depth = p_depth;
		data.resize(width * height * depth);
	}

	void resize_fill(int p_height, int p_width, int p_depth, T value) {
		height = p_height;
		width = p_width;
		depth = p_depth;
		data.resize(width * height * depth);
		data.fill(value);
	}

	const T &get(int i, int j, int k) const {
		CRASH_BAD_INDEX(i, height);
		CRASH_BAD_INDEX(j, width);
		CRASH_BAD_INDEX(k, depth);

		return data[i * width * depth + j * depth + k];
	}

	T &get(int i, int j, int k) {
		CRASH_BAD_INDEX(i, height);
		CRASH_BAD_INDEX(j, width);
		CRASH_BAD_INDEX(k, depth);

		return data.write[i * width * depth + j * depth + k];
	}

	bool operator==(const Array3D &a) const {
		if (height != a.height || width != a.width || depth != a.depth) {
			return false;
		}

		for (int i = 0; i < data.size(); i++) {
			if (a.data[i] != data[i]) {
				return false;
			}
		}
		return true;
	}
};

#endif // FAST_WFC_UTILS_ARRAY3D_HPP_
