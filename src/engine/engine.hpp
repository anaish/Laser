#pragma once
#include <glog/logging.h>
#include <memory>
#include "rule.hpp"

typedef std::tr1::shared_ptr<Rule> PRule;

class Engine {
public:
	Engine(PRule rule);
	void run();
private:
	PRule rule;
};
