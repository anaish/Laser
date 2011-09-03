
#include <GL/gl.h>
#include "defaultphysics.hpp"


DefaultPhysics::DefaultPhysics(){

}

void DefaultPhysics::setDisplay(PDisplay display){

	assert(display);

	this->display = display;

}

void DefaultPhysics::onEvent(SDL_Event* event){

	switch(event->type){

		case SDL_MOUSEMOTION:
			display->rotateScene(5.0,0.f,1.f,0.f);
			break;

	}




}
