/*
 * Copyright (C) 2004-2014 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <ZLStringUtil.h>

#include "FontManager.h"

std::string FontManager::put(const std::string &family, shared_ptr<FontEntry> entry) {
	shared_ptr<FontEntry> existing = myMap[family];
	if (existing.isNull() || *existing == *entry) {
		myMap[family] = entry;
		return family;
	}

	for (std::map<std::string,shared_ptr<FontEntry> >::const_iterator it = myMap.begin(); it != myMap.end(); ++it) {
		if (*it->second == *entry) {
			return it->first;
		}
	}

	for (int i = 1; i < 1000; ++i) {
		std::string indexed = family + "#";
		ZLStringUtil::appendNumber(indexed, i);
		if (myMap[indexed].isNull()) {
			myMap[indexed] = entry;
			return indexed;
		}
	}

	return std::string();
}
