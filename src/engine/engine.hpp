#pragma once
#include <glog/logging.h>
#include <tr1/memory>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "rule.hpp"
#include "display.hpp"
#include "config.hpp"

typedef std::tr1::shared_ptr<Rule> PRule;
typedef std::tr1::shared_ptr<Display> PDisplay;
typedef std::tr1::shared_ptr<Config> PConfig;


class Engine {
public:
	Engine(PRule rule);
	void init();
	void run();
	void setDisplay(PDisplay display);
	void setConfig(PConfig config);
private:
	PRule rule;
	PDisplay display;
	PConfig config;
};
