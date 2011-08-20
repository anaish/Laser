/*
 * assimpmodelimporter.hpp
 *
 *  Created on: Aug 11, 2011
 *      Author: andrew
 */
#pragma once
#include "../engine/modelimporter.hpp"
#include <assimp/assimp.h>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>
#include <string>

using namespace std;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)




class AssimpModelImporter : public ModelImporter {

public:
	AssimpModelImporter();
	virtual void init(PConfig config);
private:
	void get_bounding_box_for_node (const struct aiNode* nd,
	struct aiVector3D* min,
	struct aiVector3D* max,
	struct aiMatrix4x4* trafo
	);
	void get_bounding_box (struct aiVector3D* min, struct aiVector3D* max);
	PConfig config;
	struct aiVector3D scene_min, scene_max, scene_center;
	void loadModel(string fileName);


};
