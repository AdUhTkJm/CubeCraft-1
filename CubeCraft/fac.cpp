#pragma once
#pragma warning(disable: 4996)
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"fac.h"

GLuint texts[100];

GLuint glLoadTex(const char* file_name) {
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLint last_texture_ID;
	GLuint texture_ID = 0;
	FILE* pFile = fopen(file_name, "rb");
	if (!pFile) return 0;

	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, 54, SEEK_SET);

	GLint line_bytes = width * 3;
	while (line_bytes % 4 != 0)
		++line_bytes;
	total_bytes = line_bytes * height;

	pixels = (GLubyte*)malloc(total_bytes);

	if (fread(pixels, total_bytes, 1, pFile) <= 0) {
		free(pixels);
		fclose(pFile);
		return 0;
	}

	glGenTextures(1, &texture_ID);
	if (!texture_ID) {
		free(pixels);
		fclose(pFile);
		return 0;
	}

	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 64, 64, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	//glBindTexture(GL_TEXTURE_2D, last_texture_ID);
	free(pixels);
	return texture_ID;
}


void glString(const char* str) {
	static bool a = 1;
	static GLuint lists;
	if (a) a = !a,
		lists = glGenLists(128),
		wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, lists);
	while (*str)
		glCallList(lists + *str++);
}
