/*
 * defaultphysics.hpp
 *
 *  Created on: Aug 31, 2011
 *      Author: andrew
 */
#pragma once
#include "../engine/physics.hpp"
#include <cassert>
#include <SDL/SDL.h>
#include <ode/ode.h>


#ifndef DEFAULTPHYSICS_HPP_
#define DEFAULTPHYSICS_HPP_

class DefaultPhysics : public Physics {

public:
	DefaultPhysics();
	virtual void setDisplay(PDisplay display);
	virtual void onEvent(SDL_Event* event);
private:
	PDisplay display;


};

#endif
