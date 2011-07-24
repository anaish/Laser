#pragma once
#include <glog/logging.h>
#include <tr1/memory>
// #include <tr1/shared_ptr.h>
#include "rule.hpp"

typedef std::tr1::shared_ptr<Rule> PRule;

class Engine {
public:
	Engine(PRule rule);
	void run();
private:
	PRule rule;
};
