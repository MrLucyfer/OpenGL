#pragma once
#include <GLCore.h>
#include "PerspectiveCamera.h"

class PerspectiveCameraController {
public:
	PerspectiveCameraController();
	~PerspectiveCameraController();

	inline PerspectiveCamera getCamera() const { return m_Camera; }
	inline float getCameraSpeed() const { return cameraSpeed; }
	inline glm::vec3 getCameraPos() const { return m_CameraPos; };

	void setCameraSpeed(const float& speed);

	void LookAt();
	void LookAt(glm::vec3 camPos);
	void Update(GLCore::Timestep ts);
private:

	float zoomLevel;
	float cameraSpeed;
	float m_MouseSensitivity = 0.1f;

	bool mousePressed = false;

	float lastX = 640.0f;
	float lastY = 300.0f;

	float yaw = -90.0f;
	float pitch = 0.0f;

	PerspectiveCamera m_Camera;

	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraTarget;
	glm::vec3 m_CameraDirection;
	glm::vec3 m_CameraFront;

	glm::vec3 m_Up;
};