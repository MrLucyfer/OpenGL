#include "PerspectiveCameraController.h"
#include <GLCore/Core/Input.h>
#include <GLCore/Core/KeyCodes.h>
#include <GLCore/Core/MouseButtonCodes.h>

using namespace GLCore;

PerspectiveCameraController::PerspectiveCameraController() :
	m_CameraPos{ 0.0f, 0.0f, 3.0f }, m_CameraTarget{ 0.0f, 0.0f, 0.0f },
	m_Up{ 0.0, 1.0f, 0.0f }, m_CameraFront{ 0.0f, 0.0f, -1.0f }, zoomLevel(1.0f), cameraSpeed(0.01f)
{
	m_CameraDirection = m_CameraTarget - m_CameraPos;
	m_Camera.Translate(m_CameraDirection);
}

PerspectiveCameraController::~PerspectiveCameraController()
{
}

void PerspectiveCameraController::LookAt() {
	glm::mat4 lookAt = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_Up);
	m_Camera.setView(lookAt);
}

void PerspectiveCameraController::LookAt(glm::vec3 camPos) {
	glm::mat4 lookAt = glm::lookAt(camPos, m_CameraTarget, m_Up);
	m_Camera.setView(lookAt);
}

void PerspectiveCameraController::setCameraSpeed(const float& speed) {
	cameraSpeed = speed;
}

void PerspectiveCameraController::Update(Timestep ts)
{
	if (Input::IsKeyPressed(HZ_KEY_W)) {
		m_CameraPos += (cameraSpeed * m_CameraFront * ts.GetMilliseconds());
	}
	if (Input::IsKeyPressed(HZ_KEY_A)) {
		m_CameraPos -= (glm::normalize(glm::cross(m_CameraFront, m_Up)) * cameraSpeed * ts.GetMilliseconds());
	} 
	if (Input::IsKeyPressed(HZ_KEY_S)) {
		m_CameraPos -= (cameraSpeed * m_CameraFront * ts.GetMilliseconds());
	}
	if (Input::IsKeyPressed(HZ_KEY_D)) {
		m_CameraPos += (glm::normalize(glm::cross(m_CameraFront, m_Up)) * cameraSpeed * ts.GetMilliseconds());
	}
	if (Input::IsMouseButtonPressed(HZ_MOUSE_BUTTON_2)) {
		float actualX = Input::GetMouseX();
		float actualY = Input::GetMouseY();
		if (!mousePressed) {
			lastX = actualX;
			lastY = actualY;
			mousePressed = true;
		}
		//Rotate IDK how
		
		float offSetX = (actualX - lastX) * m_MouseSensitivity;
		float offSetY = (lastY - actualY) * m_MouseSensitivity;
		lastX = actualX;
		lastY = actualY;
		
		yaw += offSetX;
		pitch += offSetY;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		m_CameraFront = glm::normalize(direction);
	}
	else {
		mousePressed = false;
	}

	LookAt();
}
