#pragma once

#include "R_Mesh.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

using namespace std;

#define VERTEX_ARGUMENTS 5
class GameObject;
//class M_Mesh;

class MeshLoader : public M_Mesh {
public:
	MeshLoader();
	~MeshLoader();


	static void StartDebugMode();
	static void StopDebugMode();
	
	static M_Mesh* LoadMesh(aiMesh* importedMesh);
	static M_Mesh* LoadFile(string file_path, GameObject* parent);

	static void Renderer();
	static void CleanUp();


	static GameObject* gameObjectReturned;

private:

	


};


