#include "engine.hpp"

Engine::Engine(PRule rule) {
	LOG(ERROR) << "Rule loaded ";
	this->rule = rule;
}
/**
Initialises the engine (view port/controls/levels/etc), and then starts the game loop
**/
void Engine::init() {


	display->init();

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

void Engine::setDisplay(PDisplay display){

	LOG(ERROR) << "Init Display";
	this->display = display;
	

}

/**
Runs this engine's current rule
**/

void Engine::run() {
	LOG(ERROR) << "Running engine with rule - " + rule->getName();
	rule->run();
	LOG(ERROR) << "Ran the engine, all done now.";
}



