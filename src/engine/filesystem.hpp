/*
 * filesystem.hpp
 *
 *  Created on: Aug 8, 2011
 *      Author: andrew
 */

#pragma once
#include <string>

using namespace std;


class FileSystem {

public:
	virtual string readFile(string fullPath) = 0;
	virtual string getHomeDirectory() = 0;
	virtual ~FileSystem(){}

};
