#include"block.h"
#include"fac.h"

Block visible[64][64][64], invalid;

Block& at(int a, int b, int c) {
	if (a >= 64 || b >= 64 || c >= 64 || a < 0 || b < 0 || c < 0) return invalid;
	return visible[a][b][c];
}

void Block::draw() {
	int fr, bk, lt, rt, up, dn;
	switch (id) {
	case air:
		return;
	case dirt:
		fr = bk = lt = rt = up = dn = 0; break;
	case grass:
		up = 1; bk = lt = rt = fr = dn = 2; break;
	case stone:
		fr = bk = lt = rt = up = dn = 3; break;
	case bedrock:
		fr = bk = lt = rt = up = dn = 4; break;
	}
	float x = t.x, y = t.y, z = t.z;
	if (at(t.x, t.y, t.z - 1).id == air) {  //front
		glBindTexture(GL_TEXTURE_2D, texts[fr]);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f + x, 0.0f + y, 1.0f + z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f + x, 0.0f + y, 1.0f + z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f + x, 1.0f + y, 1.0f + z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f + x, 1.0f + y, 1.0f + z);
		glEnd();
	}
	if (at(t.x, t.y, t.z + 1).id == air) { //back
		glBindTexture(GL_TEXTURE_2D, texts[bk]);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f + x, 0.0f + y, 0.0f + z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f + x, 1.0f + y, 0.0f + z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f + x, 1.0f + y, 0.0f + z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f + x, 0.0f + y, 0.0f + z);
		glEnd();
	}
	if (at(t.x + 1, t.y, t.z).id == air) { //right
		glBindTexture(GL_TEXTURE_2D, texts[rt]);
		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f + x, 0.0f + y, 0.0f + z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f + x, 1.0f + y, 0.0f + z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f + x, 1.0f + y, 1.0f + z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f + x, 0.0f + y, 1.0f + z);
		glEnd();
	}
	if (at(t.x - 1, t.y, t.z).id == air) { //left
		glBindTexture(GL_TEXTURE_2D, texts[lt]);
		glBegin(GL_QUADS);
		glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f + x, 0.0f + y, 0.0f + z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f + x, 0.0f + y, 1.0f + z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f + x, 1.0f + y, 1.0f + z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f + x, 1.0f + y, 0.0f + z);
		glEnd();
	}
	if (at(t.x, t.y + 1, t.z).id == air) { //up
		glBindTexture(GL_TEXTURE_2D, texts[up]);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f + x, 1.0f + y, 0.0f + z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f + x, 1.0f + y, 1.0f + z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f + x, 1.0f + y, 1.0f + z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f + x, 1.0f + y, 0.0f + z);
		glEnd();
	}
	if (at(t.x, t.y - 1, t.z).id == air) { //down
		glBindTexture(GL_TEXTURE_2D, texts[dn]);
		glBegin(GL_QUADS);
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f + x, 0.0f + y, 0.0f + z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f + x, 0.0f + y, 0.0f + z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f + x, 0.0f + y, 1.0f + z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f + x, 0.0f + y, 1.0f + z);
		glEnd();
	}
}