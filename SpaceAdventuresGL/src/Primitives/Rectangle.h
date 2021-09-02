#pragma once
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 Position;
	//glm::vec4 Color
};

class Rectangle
{
public:
	Rectangle();
	Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	~Rectangle();

	void Draw(Shader& shader);

private:
	void InitVertexArray();
	void InitVertexBuffer();
	void InitIndexBuffer();

private:
	std::unique_ptr<VertexArray>  m_VertexArray;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer>  m_IndexBuffer;

	

private:
	glm::vec2 m_Position;
	glm::vec2 m_Size;
	glm::vec4 m_Color;
};