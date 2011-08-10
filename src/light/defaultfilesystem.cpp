#include <glog/logging.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <stdlib.h>
#include "defaultfilesystem.hpp"


using namespace std;

/**
The default file system - currently only tested in linux.
**/
DefaultFileSystem :: DefaultFileSystem(){

}

/**
 *
 */
string DefaultFileSystem::getHomeDirectory() {

	return getenv("HOME");

}


/**
 * Reads a file
 */
string DefaultFileSystem::readFile(string fileName) {

  string jsonFile;
  string line;
  ifstream myfile (fileName.c_str());
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,line);
      jsonFile += line;
    }
    myfile.close();
  }

  else LOG(ERROR) << "Unable to open file: " << fileName;

  return jsonFile;
}
