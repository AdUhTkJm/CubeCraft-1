#pragma once
#include <glm/glm.hpp>

struct Block {
	glm:: t;
	BlockType id;
	Block(Point p = Point(), BlockType ty = air): t(p), id(ty) {}
	void draw();
};

extern Block visible[64][64][64], invalid;

Block& at(int a, int b, int c);