#pragma once
#include "Player.hpp"
#include "Glob.hpp"
char name[256];

static std::string GetNameById(uint32_t actor_id) {

	uint32_t chunk_offset = actor_id >> 16;
	uint16_t name_offset = (uint16_t)actor_id;
	uintptr_t fname_pool = Functions::Base + 0x3fe3d80; // gname

	uintptr_t name_pool_chunk = driver.read<uintptr_t>(fname_pool + ((chunk_offset + 2) * 8));
	if (name_pool_chunk) {
		uintptr_t entry_offset = name_pool_chunk + (uint32_t)(2 * name_offset);
		if (entry_offset) {

			uint16_t name_entry = driver.read<uint16_t>(entry_offset);

			uint32_t name_length = (name_entry >> 6);

			if (name_length > 256)
			{
				name_length = 255;
			}

			 driver.read(entry_offset + 0x2, &name, name_length);
			return name;


		}
	}
	return std::string("NULL");
}
