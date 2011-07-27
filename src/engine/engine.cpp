#include "engine.hpp"

Engine::Engine(PRule rule) {
	LOG(ERROR) << "Rule loaded ";
	this->rule = rule;
}

void Engine::init() {

	//bool initGl = initOpenGl();
	
	//remove this:
	screen = PSurface(SDL_SetVideoMode(800,600,16, SDL_SWSURFACE));
	

	bool stillRunning = true;
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

/**
Initialises the Open GL context.
Should only be called once.
**/

bool Engine::initOpenGl() {

/*
	LOG(ERROR) << "Initialising OpenGL";

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        	return false;
    	}

    	if((Surf_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        	return false;
    	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,     32);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,  8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

*/	
	return true;

}

void Engine::run() {
	LOG(ERROR) << "Running engine with rule - " + rule->getName();
	rule->run();
	LOG(ERROR) << "Ran the engine, all done now.";
}
