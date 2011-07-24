#pragma once

#include <string>

class Rule {
public:
	virtual void run() = 0;
	std::string getName() {
		return name;
	}
	virtual ~Rule() {}
protected:
	std::string name;
};
