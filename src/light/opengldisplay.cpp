#include "opengldisplay.hpp"

OpenGlDisplay :: OpenGlDisplay(){

}

/**
Initialises the Open GL context.
Should only be called once.
**/

/*
TODO we need to pass in a configuration object here with the initialisation parameters (i.e screen width/height, antialiasing on/off, etc) they should come from config and/or auto detection.
*/


void OpenGlDisplay::init(){

	LOG(ERROR) << "Initialising OpenGL";

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        	LOG(ERROR) << "Unable to init SDL";
    	}
	
	screen = PSurface(SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF));

    	if(screen == NULL) {
        	LOG(ERROR) << "Unable to init screen";
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



} 
