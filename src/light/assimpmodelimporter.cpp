/*
 * assimpModelImporter.cpp
 *
 *  Created on: Aug 12, 2011
 *      Author: andrew
 */

#include "assimpmodelimporter.hpp"
#include <assimp/assimp.h>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>
#include <string>
#include <cassert>
#include <glog/logging.h>

using namespace std;

// the global Assimp scene object
const struct aiScene* scene = NULL;

AssimpModelImporter::AssimpModelImporter(){


}

/**
 * Returns the scene
 */
const aiScene* AssimpModelImporter::getScene(){

	return scene;
}

/**
 * gets a node by it's name - uses recursion
 */
const struct aiNode* AssimpModelImporter::getNodeByName(string nodeName,const struct aiNode* nd){

	unsigned int n = 0;

	for (; n < nd->mNumMeshes; ++n) {
		if(nd->mName.data==nodeName){
			return nd;
		}
	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n) {
		return getNodeByName(nodeName, nd->mChildren[n]);
	}

	//can't find the node
	assert(false);
	return NULL;

}

/**
 * Loads the models into the scene object
 */
void AssimpModelImporter::init(PConfig config){

	this->config = config;

	string modelFileName = config->getString("scene","filePath");
	assert(modelFileName.length()!=0);

	this->loadModel(modelFileName);


}
/*
 * Loads the model into memory from disk
 */
void AssimpModelImporter::loadModel(string fileName){

	// we are taking one of the postprocessing presets to avoid
	// writing 20 single postprocessing flags here.
	PFileSystem fileSystem = config->getFileSystem();
	string homeDirectory = fileSystem->getHomeDirectory();
	string gameDirectory = fileSystem->getGameDirectory();
	string modelPath = homeDirectory + gameDirectory + "/" + fileName;

	const char* modelFile = modelPath.c_str();

	scene = aiImportFile(modelFile,aiProcessPreset_TargetRealtime_Quality);

	assert(scene);

	if (scene) {
		get_bounding_box(scene->mRootNode,&scene_min,&scene_max);
		scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
		scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
		scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
	}

}

/**
 * Gets the bounding box for a node and assigns it to min and max.
 */

void AssimpModelImporter::get_bounding_box_for_node (const struct aiNode* nd,
	struct aiVector3D* min,
	struct aiVector3D* max,
	struct aiMatrix4x4* trafo
){
	struct aiMatrix4x4 prev;
	unsigned int n = 0, t;

	prev = *trafo;

	// TODO we will introduce an identifier into the name of the object in blender which will
	// indicate that the object is collidable something like collidable_Laser, collidable_Target
	setCollidableNodeCount(getCollidableNodeCount()+1);


	aiMultiplyMatrix4(trafo,&nd->mTransformation);

	for (; n < nd->mNumMeshes; ++n) {
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t) {

			struct aiVector3D tmp = mesh->mVertices[t];
			aiTransformVecByMatrix4(&tmp,trafo);

			min->x = aisgl_min(min->x,tmp.x);
			min->y = aisgl_min(min->y,tmp.y);
			min->z = aisgl_min(min->z,tmp.z);

			max->x = aisgl_max(max->x,tmp.x);
			max->y = aisgl_max(max->y,tmp.y);
			max->z = aisgl_max(max->z,tmp.z);
		}
	}

	for (n = 0; n < nd->mNumChildren; ++n) {
		get_bounding_box_for_node(nd->mChildren[n],min,max,trafo);
	}
	*trafo = prev;
}

/*
 * Calculates the scene's bounding box and assigns the values to min and max.
 */

void AssimpModelImporter::get_bounding_box (struct aiNode* node,struct aiVector3D* min, struct aiVector3D* max)
{
	struct aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);

	min->x = min->y = min->z =  1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(node,min,max,&trafo);
}

/**
 * Sets the number of collidable nodes
 */
void AssimpModelImporter::setCollidableNodeCount(int count){
	this->collidableNodeCount = count;
}

/**
 * Gets the number of collidable nodes
 */
int AssimpModelImporter::getCollidableNodeCount(){
	return this->collidableNodeCount;
}

