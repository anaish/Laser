#include "engine.hpp"

Engine::Engine(PRule rule) {
	LOG(ERROR) << "Rule loaded ";
	this->rule = rule;
}

void Engine::init() {
	SDL_Init(SDL_INIT_VIDEO);
	bool stillRunning = true;
	screen = PSurface(SDL_SetVideoMode(800,600,16, SDL_SWSURFACE));
	SDL_Event event;
	while(stillRunning) {
		SDL_WaitEvent(&event);
		switch( event.type ) {
			SDL_QUIT:
				stillRunning = false;
			break;
		}
	}
	SDL_Quit();
}

void Engine::run() {
	LOG(ERROR) << "Running engine with rule - " + rule->getName();
	rule->run();
	LOG(ERROR) << "Ran the engine, all done now.";
}
