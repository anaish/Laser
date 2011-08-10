#pragma once

/**
 * An interface to the display
 */
#include <string>

using namespace std;

class Config {
public:
	virtual void load(string json) = 0;
	//gets an integer parameter - eg "display","width"s
	virtual int getInt(const char* category,const char* name) = 0;
	virtual ~Config(){};
};
