#pragma once

/**
 * An interface to the display
 */
#include <string>
#include "filesystem.hpp"
#include <tr1/memory>

using namespace std;

typedef std::tr1::shared_ptr<FileSystem> PFileSystem;

class Config {
public:
	virtual void load(string jsonFileName) = 0;
	virtual void setFileSystem(PFileSystem fileSystem)=0;
	virtual PFileSystem getFileSystem()=0;
	//gets an integer parameter - eg "display","width"s
	virtual int getInt(const char* category,const char* name) = 0;
	virtual string getString(const char* category,const char* name) = 0;
private:
	PFileSystem fileSystem;
};
