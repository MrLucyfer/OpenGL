#include "Object.h"
#include "Importer.h"

Object::Object() :
	m_Shader(nullptr), m_Pos {0.0f, 0.0f, 0.0f}, m_Rotation {0.0f, 0.0f, 0.0f}, m_Scale {1.0f, 1.0f, 1.0f}
{
}

Object::Object(const std::string& path, Shader* s, PerspectiveCameraController* controller) :
	m_Shader(s), m_Pos{ 0.0f, 0.0f, 0.0f }, m_Rotation{ 0.0f, 0.0f, 0.0f }, m_Scale{ 1.0f, 1.0f, 1.0f }, m_CameraController(controller)
{
	Importer importer;
	importer.loadFile(path, vertices, indices);
	if (s == nullptr) {
		m_Shader = s;
	}
}

Object::~Object()
{
}

void Object::OnAtach()
{
	m_VAO = std::make_unique<VertexArray>();
	m_VBO = std::make_unique<VertexBuffer>(glm::value_ptr(vertices[0]), vertices.size() * sizeof(glm::vec3));
	m_IBO = std::make_unique<IndexBuffer>(&indices[0], indices.size() * sizeof(unsigned int));

	layout.Push<float>(3);
	layout.Push<float>(3);

	m_VAO->AddVertexBuffer(layout);
}

void Object::OnUpdate(Timestep ts)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, m_Pos);
	model = glm::scale(model, m_Scale);

	glUseProgram(m_Shader->GetRendererID());


	int location = glGetUniformLocation(m_Shader->GetRendererID(), "u_Model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));

	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ViewProjection");
	glm::mat4 mvp = m_CameraController->getCamera().getViewProjection() * model;
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mvp));

	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ViewPos");
	glUniform3fv(location, 1, glm::value_ptr(m_CameraController->getCameraPos()));

	m_VAO->Bind();
	glDrawElements(GL_TRIANGLES, m_IBO->getCount(), GL_UNSIGNED_INT, 0);
}

void Object::OnImGuiRender()
{
}

void Object::SetShader(Shader* s)
{
	if (s == nullptr) {
		m_Shader = s;
	}
}
