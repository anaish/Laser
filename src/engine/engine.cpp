#include "engine.hpp"

Engine::Engine(PRule rule) {
	LOG(INFO) << "Rule loaded ";
	this->rule = rule;
}

void Engine::run() {
	LOG(INFO) << "Running engine with rule - ";
	this->rule->run();
	LOG(INFO) << "Ran the engine, all done now.";
}
