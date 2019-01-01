#include "application.h"
#include "engine.h"

int main(int argc, char** argv) {
	cc::engine::init();
	cc::application app;
	app.run();
}