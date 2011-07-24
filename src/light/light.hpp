#pragma once
#include <glog/logging.h>
#include "../engine/rule.hpp"

class Light : public Rule {
public:
	Light();
	virtual void run();
};
