/*
 * Copyright (C) 2006-2014 by the Widelands Development Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef TERRAIN_DESCRIPTION_H
#define TERRAIN_DESCRIPTION_H

#include <string>

#include <boost/noncopyable.hpp>

#include "descr_maintainer.h"
#include "logic/widelands.h"
#include "logic/world/data.h"
#include "logic/world/resource_description.h"

class Section;

namespace Widelands {
// NOCOM(#sirver): rename to World::Terrain ?
struct TerrainDescription : boost::noncopyable {
	typedef Terrain_Index Index;

	// TODO(sirver): this should not take a picnametempl, but a list of paths.
	TerrainDescription(
			const std::string& name,
			const std::string &descname,
			TerrainType type,
			const std::vector<std::string>& texture_files,
			int fps,
			int32_t dither_layer,
			std::vector<uint8_t> valid_resources,
			uint8_t default_resource,
			int32_t default_amount);

	~TerrainDescription();

	// Loads all graphics related to this Terrain from disk.
	void load_graphics();

	// The name used internally for this terrain.
	const std::string& name() const;

	// The name showed to users of Widelands. Usually translated.
	const std::string& descname() const;

	// Returns the texture index for this terrain.
	uint32_t get_texture() const;

	// Returns the type of terrain this is (water, walkable, and so on).
	// // NOCOM(#sirver): inline TerrainType here
	TerrainType get_is() const;

	// Returns the value of the resource in this field.
	// NOCOM(#sirver): find out what this does.
	int32_t resource_value(const Resource_Index resource) const;

	// Returns the valid resource with the given index.
	Resource_Index get_valid_resource(uint8_t index) const;

	// Returns true if this resource can be found in this terrain type.
	bool is_resource_valid(const int32_t res) const;

	// Returns the resource index that can by default always be found in this
	// terrain.
	int8_t get_default_resource() const;

	// Returns the default amount of resources you can find in this terrain.
	int32_t get_default_resource_amount() const;

	// Returns the dither layer, i.e. the information in which zlayer this
	// texture should be drawn.
	int32_t dither_layer() const;

private:
	const std::string name_;
	const std::string descname_;
	TerrainType is_;
	const std::vector<uint8_t> valid_resources_;
	int8_t default_resource_index_;
	int32_t default_resource_amount_;
	const std::vector<std::string> texture_paths_;
	int32_t dither_layer_;
	uint32_t texture_;  //  renderer's texture
};

}  // namespace Widelands

#endif /* end of include guard: TERRAIN_DESCRIPTION_H */
