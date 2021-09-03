#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Nova {

	class Camera
	{
	public:
		Camera(float width, float height);

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

	private:
		float m_AspectRatio;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		//glm::vec3 Position;

	};
}