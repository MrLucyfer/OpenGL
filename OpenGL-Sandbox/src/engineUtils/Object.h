#pragma once
#include <string>
#include <GLCore.h>
#include <GLCoreUtils.h>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "PerspectiveCameraController.h"

using namespace GLCore;
using namespace GLCore::Utils;

class Object {
public:
	Object();
	Object(const std::string& path, Shader* s, PerspectiveCameraController* controller);
	~Object();

	void OnAtach();
	void OnUpdate(Timestep ts);
	void OnImGuiRender();

private:
	void SetShader(Shader* s);
private:
	glm::vec3 m_Pos;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
	
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;

	VertexBufferLayout layout;

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;

	PerspectiveCameraController* m_CameraController;

	Shader* m_Shader;
};