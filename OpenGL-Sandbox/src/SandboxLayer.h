#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>

#include "engineUtils/VertexArray.h"
#include "engineUtils/VertexBuffer.h"
#include "engineUtils/IndexBuffer.h"
#include "engineUtils/Renderer.h"
#include "engineUtils/Texture.h"
#include "engineUtils/PerspectiveCameraController.h"
#include "engineUtils/Importer.h"

class SandboxLayer : public GLCore::Layer
{
public:
	SandboxLayer();
	virtual ~SandboxLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(GLCore::Event& event) override;
	virtual void OnUpdate(GLCore::Timestep ts) override;
	virtual void OnImGuiRender() override;

private:
	GLCore::Utils::Shader* m_Shader;
	GLCore::Utils::Shader* m_lightShader;
	float coords[3] = {0.0f, 0.0f, 0.0f};
	float scale[3] = { 0.5f, 0.5f, 0.5f };
	float angle = 0.0f;
	float fps;
	bool rotate = false;
	bool flip = false;

	glm::vec3 lightPos = { 1.20f, 1.6f, 2.0f };

	
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<Texture> m_Texture;

	std::unique_ptr<VertexArray> l_VAO;
	std::unique_ptr<IndexBuffer> l_IBO;
	std::unique_ptr<VertexBuffer> l_VBO;

	Renderer renderer;
	Importer importer;

	std::unique_ptr<PerspectiveCameraController> m_CameraController;

	glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
	glm::vec4 m_BackgroundColor = { 0.186f, 0.186f, 0.186f, 1.0f };


};