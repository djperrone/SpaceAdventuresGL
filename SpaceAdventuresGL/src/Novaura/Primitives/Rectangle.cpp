#include "sapch.h"
#include "Rectangle.h"

namespace Novaura {
	
	Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color)
		: m_Position(position, 0.0f), m_Scale(scale, 1.0f), m_Color(color) {}

	Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& scale)
		: m_Position(position, 0.0f), m_Scale(scale, 1.0f) {}

	Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& scale, float angle)
		: m_Position(position, 0.0f), m_Scale(scale,0.0f), m_Rotation(angle)
	{
	}
	Rectangle::Rectangle(const glm::vec2& position)
		: m_Position(position, 0.0f)
	{
	}

	
}




