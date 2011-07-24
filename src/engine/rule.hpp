#pragma once

class Rule {
public:
	virtual void run() = 0;
	virtual ~Rule() {}
};
