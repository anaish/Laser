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


class AssimpModelImporter : public ModelImporter {

public:
	virtual void loadModel(const char* fileName);
private:
	void get_bounding_box_for_node (const struct aiNode* nd,
		struct aiVector3D* min,
		struct aiVector3D* max,
		struct aiMatrix4x4* trafo
	);
	void get_bounding_box (struct aiVector3D* min, struct aiVector3D* max);


};
