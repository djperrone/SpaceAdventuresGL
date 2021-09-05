#include "sapch.h"
#include "Rectangle.h"

#include <glad/glad.h>

namespace Novaura {

	Rectangle::Rectangle()
		: m_Position(0.0f,0.0f,0.0f), m_Size(1.0f,1.0f,1.0f), m_Color(0.0f,0.0f,0.0f,1.0f)
	{
		InitVertexBuffer();

	}

	Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& scale)
		: m_Position(position, 0.0f), m_Size(size, 1.0f), m_Color(color), m_Scale(scale, 1.0f)
	{
		InitVertexBuffer();
	}

	Rectangle::~Rectangle()
	{
	}

	void Rectangle::InitVertexBuffer()
	{
		constexpr unsigned int size = 28;
		float vertices[size] = {
		 -0.5f, -0.5f, 0.0f,		m_Color.r, m_Color.g, m_Color.b, m_Color.a,
		  0.5f, -0.5f, 0.0f,		m_Color.r, m_Color.g, m_Color.b, m_Color.a,
		  0.5f,  0.5f, 0.0f,		m_Color.r, m_Color.g, m_Color.b, m_Color.a,
		 -0.5f , 0.5f, 0.0f,		m_Color.r, m_Color.g, m_Color.b, m_Color.a
		};				

		m_VertexBuffer = std::make_unique<VertexBuffer>();
		m_VertexBuffer->SetData(vertices, sizeof(vertices));
	}	
}




