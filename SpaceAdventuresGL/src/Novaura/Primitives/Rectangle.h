#pragma once
#include "Novaura/Renderer/VertexArray.h"
#include "Novaura/Renderer/VertexBuffer.h"
#include "Novaura/Renderer/IndexBuffer.h"
#include "Novaura/Renderer/Shader.h"
#include <glm/glm.hpp>

#include "Novaura/Renderer/Vertex.h"

namespace Novaura {

	

	class Rectangle
	{
	public:
		Rectangle();
		Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& scale = glm::vec2(1.0f,1.0f));
		~Rectangle();		

		VertexBuffer& GetVertexBuffer() { return *m_VertexBuffer;}
		const VertexBuffer& GetVertexBuffer() const { return *m_VertexBuffer; }

	private:	
		void InitVertexBuffer();		

	private:		
		std::unique_ptr<VertexBuffer> m_VertexBuffer;

	public:
		glm::vec3 m_Position;
		glm::vec3 m_Size;
		glm::vec3 m_Scale;
		glm::vec4 m_Color;
		float m_Rotation = 0.0f;
	};
}