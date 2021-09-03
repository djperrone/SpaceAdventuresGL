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

		void CalcProjectionMatrix(float width, float height);

	private:
		float m_AspectRatio;
		//float& m_Width, m_Height;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		//glm::vec3 Position;

	};
}