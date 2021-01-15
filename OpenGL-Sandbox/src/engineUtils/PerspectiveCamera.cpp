#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float angle, float aspectRatio, float nearVal, float farVal)
	:m_Angle(angle), m_AspectRatio(aspectRatio), m_NearVal(nearVal), 
	m_FarVal(farVal), m_Projection(glm::perspective(glm::radians(angle), aspectRatio, nearVal, farVal)),
	m_View(glm::mat4(1.0f))
{
	m_View = glm::translate(m_View, glm::vec3(0.0, 0.0, -3.0f));
}

PerspectiveCamera::~PerspectiveCamera()
{
}

glm::mat4 PerspectiveCamera::getView() const
{
	return m_View;
}

glm::mat4 PerspectiveCamera::getProjection() const
{
	return m_Projection;
}

glm::mat4 PerspectiveCamera::getViewProjection() const
{
	return m_Projection * m_View;
}

void PerspectiveCamera::setView(glm::mat4 newView) {
	m_View = newView;
}

void PerspectiveCamera::Translate(glm::vec3 coords) {
	m_View = glm::translate(m_View, coords);
}

void PerspectiveCamera::Rotate(float angle, glm::vec3 rotationAxis) {
	m_View = glm::rotate(m_View, glm::radians(angle), rotationAxis);
}
