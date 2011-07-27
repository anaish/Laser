#pragma once
#include <glog/logging.h>
#include <tr1/memory>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../engine/display.hpp"

typedef std::tr1::shared_ptr<SDL_Surface> PSurface;

class OpenGlDisplay : public Display {
public:
	OpenGlDisplay();
	virtual void init();
private:
	PSurface screen;

};
