#pragma once
#include <GLCore.h>

class PerspectiveCamera {
public:
	PerspectiveCamera(float angle = 45.0f, float aspectRatio = (1280.0f/ 720.0f), float nearVal = 0.1f, float farVal = 100.0f);
	~PerspectiveCamera();

	glm::mat4 getView() const;
	glm::mat4 getProjection() const;
	glm::mat4 getViewProjection() const;

	void setView(glm::mat4 newView);

	void Translate(glm::vec3 coords);
	void Rotate(float angle, glm::vec3 rotationAxis);

private:
	glm::mat4 m_View;
	glm::mat4 m_Projection;
	float m_Angle, m_AspectRatio, m_NearVal, m_FarVal;
};