#pragma once
#include <glm/glm.hpp>
#include "blockdef.hpp"

namespace cc {
	class Block {
		glm::ivec3 pos;
		BlockType id;
		Block(glm::ivec3 pos = {}, BlockType ty = air) noexcept;
		void draw();
	};
}
