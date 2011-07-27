#pragma once
#include <glog/logging.h>
#include <tr1/memory>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "rule.hpp"
#include "display.hpp"

typedef std::tr1::shared_ptr<Rule> PRule;
typedef std::tr1::shared_ptr<Display> PDisplay;

class Engine {
public:
	Engine(PRule rule);
	void init();
	void run();
	void setDisplay(PDisplay display);
private:
	PRule rule;
	PDisplay display;
};
