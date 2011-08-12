/*
 * modelimporter.hpp
 *
 *  Created on: Aug 11, 2011
 *      Author: andrew
 */
#pragma once

class ModelImporter {

public:
	virtual void loadModel(const char** fileName) = 0;
	virtual ~ModelImporter(){}
};
