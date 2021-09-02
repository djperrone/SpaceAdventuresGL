#include "sapch.h"
#include "Rectangle.h"

#include <glad/glad.h>

Rectangle::Rectangle()
{
	m_VertexArray = std::make_unique<VertexArray>();
	InitVertexBuffer();
	InitIndexBuffer();
	InitVertexArray();
}

Rectangle::Rectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	: m_Position(position), m_Size(size), m_Color(color)
{
	m_VertexArray = std::make_unique<VertexArray>();

	InitVertexBuffer();
	InitIndexBuffer();
	InitVertexArray();
}

Rectangle::~Rectangle()
{
}

void Rectangle::Draw(Shader& shader)
{
	m_VertexArray->Bind();
	m_IndexBuffer->Bind();
	m_IndexBuffer->Bind();
	
	shader.SetUniform4f("u_Color", m_Color);
	glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

}

void Rectangle::InitVertexArray()
{
	m_VertexArray->AddBuffer(*m_VertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
}

void Rectangle::InitVertexBuffer()
{
	constexpr unsigned int size = 12;
	float vertices[size] = {
	 -0.5f, -0.5f,0.0f,
	  0.5f, -0.5f,0.0f,
	  0.5f, 0.5f,0.0f,
	 -0.5f ,0.5f,0.0f
	};

	//float vertices[12] = {

	//	   0.5f,  0.5f, 0.0f, // top right
	//	   0.5f, -0.5f, 0.0f, // bottom right
	//	  -0.5f, -0.5f, 0.0f, // bottom left
	//	  -0.5f,  0.5f, 0.0f  // top left
	//};

	m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));	
}

void Rectangle::InitIndexBuffer()
{
	constexpr unsigned int numIndices = 6;
	unsigned int indices[numIndices] = {
		0,1,2,
		2,3,0
	};
	//unsigned int indices[6] = {
	//		0, 1, 3,
	//		1, 2, 3
	//};

	m_IndexBuffer = std::make_unique <IndexBuffer>(indices, numIndices);
}




