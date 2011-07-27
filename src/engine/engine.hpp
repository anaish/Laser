#pragma once
#include <glog/logging.h>
#include <tr1/memory>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "rule.hpp"

typedef std::tr1::shared_ptr<Rule> PRule;
typedef std::tr1::shared_ptr<SDL_Surface> PSurface;

class Engine {
public:
	Engine(PRule rule);
	void init();
	void run();
	bool initOpenGl();
private:
	PRule rule;
	PSurface screen;
};
