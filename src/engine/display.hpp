#pragma once

#include "../engine/config.hpp"
#include "../light/assimpmodelimporter.hpp"



#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

typedef std::tr1::shared_ptr<Config> PConfig;
typedef std::tr1::shared_ptr<AssimpModelImporter> PModelImporter;


/**
 * An interface to the display
 */
class Display {
public:
	//initialises the display, also creates the model importer
	virtual void init(PConfig config) = 0;
	virtual PModelImporter getModelImporter() = 0;
	virtual void OnRender() = 0;
	virtual void rotateScene(float angle,float x, float y, float z)=0;
};

#endif
