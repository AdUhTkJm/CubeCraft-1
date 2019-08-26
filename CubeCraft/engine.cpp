#include "engine.h"
#include <../glfw3.h>
#include <glad/glad.h>
#include <stdexcept>

cc::engine cc::engine::e;

cc::engine::engine()
{
	gladLoadGL();
}

cc::engine::~engine()
{
	//SDL_Quit();
}
