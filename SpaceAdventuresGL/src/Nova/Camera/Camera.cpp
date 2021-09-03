#include "sapch.h"
#include "Camera.h"

namespace Nova {

	Camera::Camera(float width, float height)
		//: m_AspectRatio(width / height), m_ProjectionMatrix(glm::ortho(-m_AspectRatio, m_AspectRatio, -m_AspectRatio, m_AspectRatio, -1.0f, 1.0f)), m_ViewMatrix(glm::mat4(1.0f))
		//: m_AspectRatio(width / height), m_ProjectionMatrix(glm::ortho(0.0f, m_AspectRatio, 0.0f, m_AspectRatio, -1.0f, 1.0f)), m_ViewMatrix(glm::mat4(1.0f))
		: m_AspectRatio(width / height), m_ProjectionMatrix(glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f)), m_ViewMatrix(glm::mat4(1.0f))
	{
	}
	void Camera::CalcProjectionMatrix(float width, float height)
	{
		m_AspectRatio = (width / height);
		//m_ProjectionMatrix = glm::ortho(-m_AspectRatio, m_AspectRatio, -m_AspectRatio, m_AspectRatio, -1.0f, 1.0f);
		//m_ProjectionMatrix = glm::ortho(0.0f, m_AspectRatio, 0.0f, m_AspectRatio, -1.0f, 1.0f);
		m_ProjectionMatrix = glm::ortho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	}
}