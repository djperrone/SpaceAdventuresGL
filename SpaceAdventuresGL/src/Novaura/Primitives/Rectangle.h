#pragma once
#include <glm/glm.hpp>

namespace Novaura {	

	class Rectangle
	{
	public:
		Rectangle() = default;
		//Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& scale = glm::vec2(1.0f, 1.0f));
		Rectangle(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color);
		~Rectangle() = default;			

	public:
		glm::vec3 m_Position = glm::vec3(0.0f,0.0f,0.0f);	
		glm::vec3 m_Scale = glm::vec3(1.0f,1.0f,1.0f);
		glm::vec4 m_Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);;
		float m_Rotation = 0.0f;
	};
}