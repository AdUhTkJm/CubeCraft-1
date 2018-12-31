#pragma once
#include"fac.h"
#include"consts.h"
#include"block.h"

struct Entity {
	EntPoint t;
	int hp;
};

struct Inventory {
	struct Box {
		Block x;
		int num;
	} cont[28];
	int top;
	Inventory(): top(1) {}
};

extern Inventory inv;
extern Entity player;
const int boxmx[5] = { 1, 64, 64, 64, 64 };

bool put_inv(Block x, Inventory v = inv);