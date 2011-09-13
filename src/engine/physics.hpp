/*
 * physics.hpp
 *
 *  Created on: Aug 31, 2011
 *      Author: andrew
 */

#include "display.hpp"
#include <SDL/SDL.h>
#include <tr1/memory>


typedef std::tr1::shared_ptr<Display> PDisplay;

#ifndef PHYSICS_HPP_
#define PHYSICS_HPP_

class Physics {

public:
	virtual void onEvent(SDL_Event* event)=0;
	virtual void onLoop()=0;
	virtual void setDisplay(PDisplay display)=0;
	virtual void init()=0;

private:
	PDisplay display;

};

#endif
