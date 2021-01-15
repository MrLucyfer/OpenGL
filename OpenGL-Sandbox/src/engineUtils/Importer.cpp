#include "Importer.h"
#include "OBJ_Loader.h"
#include <iostream>
#include <vector>

using namespace objl;

Importer::~Importer()
{
}

bool Importer::loadFile(const std::string& path, std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices)
{

	Loader loader;
	loader.LoadFile(path);

	std::vector<Vertex> vert = loader.LoadedVertices;

	indices = loader.LoadedIndices;

	for (int i = 0; i < vert.size(); i++) {
		vertices.push_back(glm::vec3(vert[i].Position.X, vert[i].Position.Y, vert[i].Position.Z));
		vertices.push_back(glm::vec3(vert[i].Normal.X, vert[i].Normal.Y, vert[i].Normal.Z));
	}

	return true;
}

