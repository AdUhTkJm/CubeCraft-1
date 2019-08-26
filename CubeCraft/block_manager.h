#pragma once
#include "block.h"
#include "noncopyable.hpp"
#include <glm/glm.hpp>

namespace cc {

	class chunk {
	public:
		void set(glm::ivec3 place, block type) noexcept;
		block get(glm::ivec3 place) const noexcept;
		void render(glm::ivec3 place) const;
	private:
		block m_blocks[16][16][16];
	};

	class world : private noncopyable {
	public:
		static void set(glm::ivec3 place, block type) noexcept;
		static block get(glm::ivec3 place) noexcept;
		static void load(glm::ivec3 place) noexcept;
		static void deload(glm::ivec3 place) noexcept;
		static void render();
		static void erect();
	private:
		static chunk m_load[16][16][16];
	};

}