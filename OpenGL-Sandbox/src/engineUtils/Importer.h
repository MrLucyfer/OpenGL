#pragma once
#include <string>
#include <vector>
#include <GLCore.h>

class Importer {
public:
	Importer() : vertAttrib(0), indexAttrib(0) {};
	~Importer();
	bool loadFile(const std::string& path, std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices);
private:
	void getInfo(const std::string& path);
	unsigned int vertAttrib, indexAttrib;
};