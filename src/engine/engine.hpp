#pragma once
#include <glog/logging.h>
#include <tr1/memory>
#include <SDL/SDL.h>
#include "rule.hpp"

typedef std::tr1::shared_ptr<Rule> PRule;
typedef std::tr1::shared_ptr<SDL_Surface> PSurface;

class Engine {
public:
	Engine(PRule rule);
	void init();
	void run();
private:
	PRule rule;
	PSurface screen;
};
