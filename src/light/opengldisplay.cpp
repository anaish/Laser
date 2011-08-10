#include "opengldisplay.hpp"

/**
An opengl implementation of the Display interface.
**/
OpenGlDisplay :: OpenGlDisplay(){

}

/**
Initialises the Open GL context.
Should only be called once.
**/
void OpenGlDisplay::init(PConfig config){
	
	/*
	TODO we need to pass in a configuration object here with the initialisation parameters 
	(i.e screen width/height, antialiasing on/off, etc) they should come from config 
	and/or auto detection.
	*/

	LOG(ERROR) << "Initialising OpenGL";

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        	LOG(ERROR) << "Unable to init SDL";
    	}
	
	screen = PSurface(SDL_SetVideoMode(config->getInt("display","width"), config->getInt("display","height"), 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL));

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
	
	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640, 480, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();


} 

/**
Renders the display.

TODO The game loop calls this every time - do we want this, or should we only render when we need to?
The ultimate goal really is to not have the display affect the performance of the game - even if
we have to skip frames to achieve it.
**/
void OpenGlDisplay::OnRender(){


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glBegin(GL_QUADS);

		/*TODO here we need to draw our assets - once we get around to it, perhaps we should 
		refactor this out so that it calls an "open gl" implementation of a "game object"
		interface. That way, if we use the same engine for different games, we can create 
		other types of game objects (e.g a 2d sprite/webgl/whatever) 
		*/
		glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
		glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
		glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
		glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
	glEnd();
	SDL_GL_SwapBuffers();

}
