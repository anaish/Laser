#pragma once
#include <glog/logging.h>
#include <tr1/memory>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../engine/display.hpp"
#include "assimpmodelimporter.hpp"

typedef std::tr1::shared_ptr<AssimpModelImporter> PModelImporter;

class OpenGlDisplay : public Display {
public:
	OpenGlDisplay();
	virtual void init(PConfig config);
	virtual void OnRender();
private:
	SDL_Surface* screen;
	PModelImporter modelImporter;


};
