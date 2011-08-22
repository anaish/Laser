#include <cassert>
#include "engine.hpp"
#include <string>
using namespace std;


Engine::Engine(PRule rule) {
	LOG(ERROR) << "Rule loaded ";
	this->rule = rule;
}
/**
Initialises the engine (view port/controls/levels/etc), and then starts the game loop
**/
void Engine::init() {

	assert(config);
	assert(display);
	assert(fileSystem);

	config->setFileSystem(fileSystem);
	config->load("config.json");

	display->init(config);

	bool running = true;
	SDL_Event event;
	while(running) {
		while(SDL_PollEvent(&event)) {
			if( event.type == SDL_QUIT )
				running = false;

			display->OnRender();

		}
	}
	SDL_Quit();
}
/**
 * Sets the display on this engine
 */
void Engine::setDisplay(PDisplay display){

	LOG(ERROR) << "Setting display";
	this->display = display;

}

/**
 * Sets the display on this engine
 */
void Engine::setFileSystem(PFileSystem filesystem){

	LOG(ERROR) << "Setting file system";
	this->fileSystem = filesystem;

}


/**
 * Sets the configuration this engine will use
 */
void Engine::setConfig(PConfig config){

	LOG(ERROR) << "Setting configuration";
	this->config = config;

}

/**
Runs this engine's current rule
**/

void Engine::run() {
	LOG(ERROR) << "Running engine with rule - " + rule->getName();
	rule->run();
	LOG(ERROR) << "Ran the engine, all done now.";
}



