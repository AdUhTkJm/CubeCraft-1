#include"entity.h"
#include"block.h"

bool put_inv(Block x, Inventory v) {
	for (int i = 0; i <= v.top; ++i)
		if (v.cont[i].x.id == x.id && v.cont[i].num != boxmx[v.cont[i].x.id]) {
			++v.cont[i].num;
			return true;
		}
	if (v.top == 28) return false;
	++v.cont[++v.top].num;
	v.cont[v.top].x = x;
	return true;
}