#include "Model.h"

int Model::zomb_edges = 0;
int Model::zomb_size = 0;
float Model::zomb_points[] = { 1.0 };

int Model::tree_edges = 0;
int Model::tree_size = 0;
float Model::tree_points[] = { 1.0 };

Model::Model(string fileName)
{

	float rand_up = (rand() % 20) ;
//	float rand_down = (rand() % 20) - 10;
	t_up += 4.0 / rand_up;
	//t_down += 1.0 / rand_up;
	//float LO = -3.0;
	//float HI = 3.0;
	//float r3 =  LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
	//LO += 6;
	//HI += 6;
	//float r4 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
	////delta = -1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 +1)));

	//if (r3 > r4) {
	//	t_up = r3;
	//	t_down = r4;

	//}
	//else {
	//	t_up = r4;
	//	t_down = r3;
	//}
	if (fileName == "models/zombie.obj" && zomb_edges != 0) {

		edges = zomb_edges;
		for (size_t i = 0; i < zomb_size; i++)
		{
			points[i] = zomb_points[i];
		}
		return;
	}
	
	if (fileName == "models/tree.obj" && tree_edges != 0) {

		edges = tree_edges;
		for (size_t i = 0; i < tree_size; i++)
		{
			points[i] = tree_points[i];
		}
		return;
	}

	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // slouèení malých plošek
		| aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodnì duplikuje
		| aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy
	const aiScene* scene = importer.ReadFile(fileName, importOptions);
	vector<float> data;
	if (scene) {
		aiMesh* mesh = scene->mMeshes[0];
		edges = mesh->mNumFaces * 3;
		if (fileName == "models/zombie.obj")
			zomb_edges = edges;
		if (fileName == "models/tree.obj")
			tree_edges = edges;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			for (unsigned int j = 0; j < 3; j++)
			{
				data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].x);
				data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].y);
				data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].z);
				data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].x);
				data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].y);
				data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].z);
				data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x);
				data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y);
			}
		}
		if (fileName == "models/zombie.obj")
			zomb_size = data.size();
		else if (fileName == "models/tree.obj")
			tree_size = data.size();
		for (size_t i = 0; i < data.size(); i++)
		{
			points[i] = data[i];
			if (fileName == "models/zombie.obj")
				zomb_points[i] = data[i];
			else if (fileName == "models/tree.obj")
				tree_points[i] = data[i];
		}
	}
}
