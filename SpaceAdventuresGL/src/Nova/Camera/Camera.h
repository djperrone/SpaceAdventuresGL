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
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void SetProjectionMatrix(float width, float height);
		void CalcProjectionMatrix();
		void CalcViewMatrix();
		void CalcViewProjectionMatrix();

	private:
		float m_AspectRatio;
		float m_Width, m_Height;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 Position{glm::vec3(0.0f,0.0f,0.0f)};

	};
}