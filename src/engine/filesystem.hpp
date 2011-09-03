/*
 * filesystem.hpp
 *
 *  Created on: Aug 8, 2011
 *      Author: andrew
 */

#pragma once
#include <string>

using namespace std;

#ifndef FILESYSTEM_HPP_
#define FILESYSTEM_HPP_

class FileSystem {

public:
	virtual string readFile(string fullPath) = 0;
	virtual string getHomeDirectory() = 0;
	virtual string getGameDirectory() = 0;

};

#endif
