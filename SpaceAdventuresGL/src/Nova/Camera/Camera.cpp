#include "sapch.h"
#include "Camera.h"

namespace Nova {

	Camera::Camera(float width, float height)
		: m_AspectRatio(width / height), m_Width(width), m_Height(height), m_ProjectionMatrix(glm::ortho(-m_AspectRatio, m_AspectRatio, -1.0f, 1.0f, -1.0f, 1.0f)), m_ViewMatrix(glm::mat4(1.0f))
		//: m_AspectRatio(width / height), m_Width(width), m_Height(height), m_ProjectionMatrix(glm::ortho(0.0f, m_AspectRatio, 0.0f, m_AspectRatio, -1.0f, 1.0f)), m_ViewMatrix(glm::mat4(1.0f))
		//: m_AspectRatio(width / height), m_Width(width), m_Height(height), m_ProjectionMatrix(glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f)), m_ViewMatrix(glm::mat4(1.0f))
	{
		CalcViewMatrix();
		CalcProjectionMatrix();
		CalcViewProjectionMatrix();
	}
	void Camera::SetProjectionMatrix(float width, float height)
	{
		m_AspectRatio = (width / height);
		m_Width = width;
		m_Height = height;
		//m_ProjectionMatrix = glm::ortho(-m_AspectRatio, m_AspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
		//m_ProjectionMatrix = glm::ortho(0.0f, m_AspectRatio, 0.0f, m_AspectRatio, -1.0f, 1.0f);
		//m_ProjectionMatrix = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
		CalcProjectionMatrix();
	}
	void Camera::CalcProjectionMatrix()
	{
		m_ProjectionMatrix = glm::ortho(-m_AspectRatio, m_AspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
		//m_ProjectionMatrix = glm::ortho(0.0f, m_Width, 0.0f, m_Height, -1.0f, 1.0f);

	}
	void Camera::CalcViewMatrix()
	{
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), Position);
	}
	void Camera::CalcViewProjectionMatrix()
	{
		CalcProjectionMatrix();
		CalcViewMatrix();
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}