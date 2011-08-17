/*
 * modelimporter.hpp
 *
 *  Created on: Aug 11, 2011
 *      Author: andrew
 */
#pragma once
#include <tr1/memory>
#include "config.hpp"
#include <string>

using namespace std;

typedef std::tr1::shared_ptr<Config> PConfig;

class ModelImporter {

public:
	virtual void init(PConfig config) = 0;
	virtual void loadModel(string fileName) = 0;
	virtual ~ModelImporter(){}

};
