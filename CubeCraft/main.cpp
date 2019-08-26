#include "application.h"
#include "engine.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(int argc, char** argv) {
	cc::application app;
	try {
		app.run();
	} catch (std::exception& a) {
		printf(a.what());
	} catch (...) {
		printf("Unknown\n");
	}
}