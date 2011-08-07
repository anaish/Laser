/*
 * v8config.hpp
 *
 *  Created on: Aug 4, 2011
 *      Author: andrew
 */
#pragma once
#include <string>
#include "../engine/filesystem.hpp"

using namespace std;


class DefaultFileSystem : public FileSystem{

public:

	DefaultFileSystem();
	virtual string getHomeDirectory();
	virtual string readFile(string fileName);

};

