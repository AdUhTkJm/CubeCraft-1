#include"block_manager.h"
#include"entity.h"

void cc::chunk::set(glm::ivec3 place, block type) noexcept {
	if (place.x >= 16 || place.y >= 16 || place.z >= 16 || place.x < 0 || place.y < 0 || place.z < 0)
		return;
	m_blocks[place.x][place.y][place.z] = type;
}

cc::block cc::chunk::get(glm::ivec3 place) const noexcept {
	if (place.x >= 16 || place.y >= 16 || place.z >= 16 || place.x < 0 || place.y < 0 || place.z < 0)
		return air;
	return m_blocks[place.x][place.y][place.z];
}

void cc::chunk::render(glm::ivec3 place) const {
	for (int i = 0; i < 16; ++i)
		for (int j = 0; j < 16; ++j)
			for (int k = 0; k < 16; ++k)
				m_blocks[i][j][k].draw(glm::ivec3(i, j, k) + place);
}

void cc::world::set(glm::ivec3 place, block type) noexcept {
	place -= ent_player.position();
	glm::ivec3 t(abs(place.x) % 16, abs(place.y) % 16, abs(place.z) % 16), r = (place - t) / 16;
	if (r.x >= 16 || r.y >= 16 || r.z >= 16 || r.x < 0 || r.y < 0 || r.z < 0)
		return;
	m_load[r.x][r.y][r.z].set(t, type);
}

cc::block cc::world::get(glm::ivec3 place) noexcept {
	place -= (glm::ivec3)ent_player.position();
	glm::ivec3 t(abs(place.x) % 16, abs(place.y) % 16, abs(place.z) % 16), r = (place - t) / 16;
	if (r.x >= 16 || r.y >= 16 || r.z >= 16 || r.x < 0 || r.y < 0 || r.z < 0)
		return air;
	return m_load[r.x][r.y][r.z].get(t);
}

void cc::world::load(glm::ivec3 place) noexcept {
	//TODO
}

void cc::world::deload(glm::ivec3 place) noexcept {
	//TODO
}

cc::chunk cc::world::m_load[16][16][16];

void cc::world::render() {
	/*for (int i = 0; i < 32; ++i)
		for (int j = 0; j < 32; ++j)
			for (int k = 0; k < 32; ++k)
				block_manager::get(glm::ivec3(i, j, k) += ent_player.position()).draw(glm::ivec3(i, j, k));*/
	for (int i = 0; i < 16; ++i)
		for (int j = 0; j < 16; ++j)
			for (int k = 0; k < 16; ++k)
				m_load[i][j][k].render(/* TODO */);
	//TODO 2: LOAD CHUNK
}

void cc::world::erect() {
	for (int i = 0; i < 64; ++i)
		for (int k = 0; k < 64; ++k)
			world::set(glm::ivec3(i, 0, k), bedrock);
	for (int i = 0; i < 64; ++i)
		for (int j = 1; j < 6; ++j)
			for (int k = 0; k < 64; ++k)
				world::set(glm::ivec3(i, j, k), stone);
	for (int i = 0; i < 64; ++i)
		for (int j = 6; j < 10; ++j)
			for (int k = 0; k < 64; ++k)
				world::set(glm::ivec3(i, j, k), dirt);
	for (int i = 0; i < 64; ++i)
		for (int k = 0; k < 64; ++k)
			world::set(glm::ivec3(i, 10, k), grass);
}