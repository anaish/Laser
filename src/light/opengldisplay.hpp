#pragma once
#include <glog/logging.h>
#include <tr1/memory>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../engine/display.hpp"
#include "assimpmodelimporter.hpp"
#include <assimp/assimp.h>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>


typedef std::tr1::shared_ptr<AssimpModelImporter> PModelImporter;

#ifndef OPENGLDISPLAY_HPP_
#define OPENGLDISPLAY_HPP_

class OpenGlDisplay : public Display {
public:
	OpenGlDisplay();
	virtual void init(PConfig config);
	virtual void OnRender();
	virtual PModelImporter getModelImporter();
	virtual void rotateScene(float angle,float x,float y, float z);
private:
	void apply_material(const struct aiMaterial *mtl);
	void set_float4(float f[4], float a, float b, float c, float d);
	void color4_to_float4(const struct aiColor4D *c, float f[4]);
	void recursive_render (const struct aiScene *sc, const struct aiNode* nd);
	void color4f(const struct aiColor4D *color);
	void render(void);
	void doMotion();
	SDL_Surface* screen;
	PModelImporter modelImporter;
	int getCollidableNodeCount;

};
#endif
