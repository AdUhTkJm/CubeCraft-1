#include "application.h"
#include "window.h"
#include <SDL/SDL.h>
#include <GL/glew.h>

cc::application::application()
	:m_window("CubeCraft")
{

}

void cc::application::run()
{
	while (running) {
		cc::Event e;
		while (m_window.poll_event(e)) {
			if (e.type = SDL_QUIT) {
				running = false;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);
		m_window.swap_buffers();
	}
}
