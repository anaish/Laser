/*
 * assimpmodelimporter.hpp
 *
 *  Created on: Aug 11, 2011
 *      Author: andrew
 */
#pragma once
#include "../engine/config.hpp"
#include <assimp/assimp.h>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>
#include <string>

using namespace std;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)


typedef std::tr1::shared_ptr<Config> PConfig;

#ifndef ASSIMPMODELIMPORTER_HPP_
#define ASSIMPMODELIMPORTER_HPP_

class AssimpModelImporter {

public:
	AssimpModelImporter();
	void init(PConfig config);
	const aiScene* getScene();
	struct aiVector3D scene_min, scene_max, scene_center;
	const struct aiNode* getNodeByName(string nodeName,const struct aiNode* nd);
	int getCollidableNodeCount();
	void setCollidableNodeCount(int count);
	void get_bounding_box (struct aiNode* node,struct aiVector3D* min, struct aiVector3D* max);

private:
	void get_bounding_box_for_node (const struct aiNode* nd,
	struct aiVector3D* min,
	struct aiVector3D* max,
	struct aiMatrix4x4* trafo
	);
	void loadModel(string fileName);
	PConfig config;
	int collidableNodeCount;
};

#endif
