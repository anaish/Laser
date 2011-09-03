#pragma once

#include <string>

#ifndef RULE_HPP_
#define RULE_HPP_


class Rule {
public:
	virtual void run() = 0;
	std::string getName() {
		return name;
	}
protected:
	std::string name;
};

#endif
