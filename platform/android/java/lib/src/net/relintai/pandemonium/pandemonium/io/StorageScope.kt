/*************************************************************************/
/*  StorageScope.kt                                                      */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
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

package net.relintai.pandemonium.pandemonium.io

import android.content.Context
import android.os.Build
import android.os.Environment
import java.io.File

/**
 * Represents the different storage scopes.
 */
internal enum class StorageScope {
	/**
	 * Covers internal and external directories accessible to the app without restrictions.
	 */
	APP,

	/**
	 * Covers shared directories (from Android 10 and higher).
	 */
	SHARED,

	/**
	 * Everything else..
	 */
	UNKNOWN;

	companion object {
		/**
		 * Determines which [StorageScope] the given path falls under.
		 */
		fun getStorageScope(context: Context, path: String?): StorageScope {
			if (path == null) {
				return UNKNOWN
			}

			val pathFile = File(path)
			if (!pathFile.isAbsolute) {
				return UNKNOWN
			}

			val canonicalPathFile = pathFile.canonicalPath

			val internalAppDir = context.filesDir.canonicalPath ?: return UNKNOWN
			if (canonicalPathFile.startsWith(internalAppDir)) {
				return APP
			}

			val internalCacheDir = context.cacheDir.canonicalPath ?: return UNKNOWN
			if (canonicalPathFile.startsWith(internalCacheDir)) {
				return APP
			}

			val externalAppDir = context.getExternalFilesDir(null)?.canonicalPath ?: return UNKNOWN
			if (canonicalPathFile.startsWith(externalAppDir)) {
				return APP
			}

			val sharedDir =	Environment.getExternalStorageDirectory().canonicalPath ?: return UNKNOWN
			if (canonicalPathFile.startsWith(sharedDir)) {
				if (Build.VERSION.SDK_INT < Build.VERSION_CODES.R) {
					// Before R, apps had access to shared storage so long as they have the right
					// permissions (and flag on Q).
					return APP
				}

				// Post R, access is limited based on the target destination
				// 'Downloads' and 'Documents' are still accessible
				val downloadsSharedDir =
					Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS).canonicalPath
						?: return SHARED
				val documentsSharedDir =
					Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS).canonicalPath
						?: return SHARED
				if (canonicalPathFile.startsWith(downloadsSharedDir) || canonicalPathFile.startsWith(documentsSharedDir)) {
					return APP
				}

				return SHARED
			}

			return UNKNOWN
		}
	}
}