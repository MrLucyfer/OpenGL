#include "SandboxLayer.h"
#include "stb_image/stb_image_write.h"
#include <vector>
#include "engineUtils/OBJ_Loader.h"


using namespace GLCore;
using namespace GLCore::Utils;


SandboxLayer::SandboxLayer():fps(0.0f)
{
	
}

SandboxLayer::~SandboxLayer()
{

}

void SandboxLayer::OnAttach()
{
	EnableGLDebugging();
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	m_Shader = Shader::FromGLSLTextFiles(
		"assets/shaders/test.vert.glsl",
		"assets/shaders/test.frag.glsl"
	);

	m_lightShader = Shader::FromGLSLTextFiles(
		"assets/shaders/test.vert.glsl",
		"assets/shaders/lightShader.glsl"
	);


	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;

	if (importer.loadFile("assets/models/teapot.obj", vertices, indices)) {
		Log::GetLogger()->info("Model Loaded!");
	}
	else {
		Log::GetLogger()->error("There was a problem loading the model :(");
	}

	m_CameraController = std::make_unique<PerspectiveCameraController>();

	m_VAO = std::make_unique<VertexArray>();
	m_VBO = std::make_unique<VertexBuffer>(glm::value_ptr(vertices[0]), vertices.size() * sizeof(glm::vec3));
	VertexBufferLayout layout;
	//Position
	layout.Push<float>(3);
	//Normal
	layout.Push<float>(3);

	m_VAO->AddVertexBuffer(layout);
	m_IBO = std::make_unique<IndexBuffer>(&indices[0], indices.size() * sizeof(unsigned int));

	glUseProgram(m_lightShader->GetRendererID());

	glUseProgram(m_Shader->GetRendererID());
}


void SandboxLayer::OnDetach()
{
	
}

void SandboxLayer::OnEvent(Event& event)
{
	
}

void SandboxLayer::OnUpdate(Timestep ts)
{
	m_CameraController->Update(ts);
	glClearColor(m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, m_BackgroundColor.a);
	renderer.Clear();

	glUseProgram(m_Shader->GetRendererID());

	int location = glGetUniformLocation(m_Shader->GetRendererID(), "lightColor");
	glUniform3f(location, 1.0f, 1.0f, 1.0f);

	location = glGetUniformLocation(m_Shader->GetRendererID(), "objectColor");
	glUniform3f(location, 1.0f, 0.5f, 0.31f);

	location = glGetUniformLocation(m_Shader->GetRendererID(), "lightPos");
	glUniform3fv(location, 1, glm::value_ptr(lightPos));

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(scale[0], scale[1], scale[2]));
	model = glm::translate(model, glm::vec3(coords[0], coords[1], coords[2]));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_Model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));

	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ViewProjection");
	glm::mat4 mvp = m_CameraController->getCamera().getViewProjection() * model;
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mvp));

	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ViewPos");
	glUniform3fv(location, 1, glm::value_ptr(m_CameraController->getCameraPos()));

	m_VAO->Bind();
	renderer.Draw(*m_VAO, *m_VBO, *m_IBO);

	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	if (flip) {
		const float radius = 10.0f;
		float camX = sin(ts.GetTotalTime()) * radius;
		float camZ = cos(ts.GetTotalTime()) * radius;
		model = glm::translate(model, glm::vec3(camX, 0, camZ));
		lightPos.x = camX;
		lightPos.z = 2 -camZ;
	}


	glUseProgram(m_lightShader->GetRendererID());
	location = glGetUniformLocation(m_lightShader->GetRendererID(), "u_ViewProjection");
	mvp = m_CameraController->getCamera().getViewProjection() * model;
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mvp));


	renderer.Draw(*m_VAO, *m_VBO, *m_IBO);
}

void SandboxLayer::OnImGuiRender()
{
	ImGui::Begin("Controls");
	ImGui::ColorEdit4("Background Color", glm::value_ptr(m_BackgroundColor));
	ImGui::DragFloat3("Translate", coords, 0.01f, -1.0f, 1.0f);
	ImGui::DragFloat3("Scale", scale, 0.01f, -2.0f, 2.0f);
	ImGui::DragFloat("Rotate Z", &angle, 5.0f, 0.0f, 360.0f);
	ImGui::Checkbox("Flip X", &flip);
	ImGui::Text("FPS: %.1", 1.0f/fps);
	ImGui::End();
}
