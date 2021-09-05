#pragma once
#include "Camera.h"
#include "Nova/Core/Window.h"

namespace Nova {

	class CameraController
	{
	public:
		CameraController(float width, float height);
		void Update(Window& window, float deltaTime);

		void ProcessMouseScroll(double yoffset);

		const Camera& GetCamera() const { return m_Camera; }
		Camera& GetCamera() { return m_Camera; }


	private:
		Camera m_Camera;
		glm::vec3 m_Position{ glm::vec3(0.0f,0.0f,0.0f) };
		float m_Rotation = 45.0f;
		float m_Zoom = 0.0f;
		float m_CameraSpeed = 0.5;
		float m_RotationSpeed = 50.0f;
	};
}