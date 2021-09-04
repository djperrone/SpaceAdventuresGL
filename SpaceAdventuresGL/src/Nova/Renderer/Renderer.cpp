#include "sapch.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Nova/Renderer/Vertex.h"
#include <glm/ext/matrix_transform.hpp>

namespace Nova {

	struct RenderData
	{	
		std::unique_ptr<VertexArray> VertexArray;
		std::unique_ptr<IndexBuffer> IndexBuffer;
		std::unique_ptr<VertexBuffer> VertexBuffer;

		glm::vec4 DefaultRectangleVertices[4];		
	};

	const Camera* SceneCamera = nullptr;

	static RenderData s_RenderData;

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, 1.0f);
	}	

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Renderer::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);

		s_RenderData.VertexArray = std::make_unique<VertexArray>();
		s_RenderData.VertexBuffer = std::make_unique<VertexBuffer>();

		constexpr unsigned int numIndices = 6;
		unsigned int indices[numIndices] = {
			0,1,2,
			2,3,0
			/*0,1,3,
			1,2,3*/
		};		

		s_RenderData.IndexBuffer = std::make_unique <IndexBuffer>(indices, numIndices);
		 // aspect ratio
		s_RenderData.DefaultRectangleVertices[0] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
		s_RenderData.DefaultRectangleVertices[1] = glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f);
		s_RenderData.DefaultRectangleVertices[2] = glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f);
		s_RenderData.DefaultRectangleVertices[3] = glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f);

		/*s_RenderData.DefaultRectangleVertices[0] = glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
		s_RenderData.DefaultRectangleVertices[1] = glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
		s_RenderData.DefaultRectangleVertices[2] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
		s_RenderData.DefaultRectangleVertices[3] = glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);*/
			
			
			

		
		// no aspect ratio
		/*s_RenderData.DefaultRectangleVertices[0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		s_RenderData.DefaultRectangleVertices[1] = glm::vec4(100.0f, 0.0f, 0.0f, 1.0f);
		s_RenderData.DefaultRectangleVertices[2] = glm::vec4(100.0f, 100.0f, 0.0f, 1.0f);
		s_RenderData.DefaultRectangleVertices[3] = glm::vec4(0.0f, 100.0f, 0.0f, 1.0f);*/
	}
	
	void Renderer::BeginScene(Shader& shader, const Camera& camera)
	{
		//SceneCamera = &camera;
		shader.Bind();
		
		shader.SetUniformMat4f("u_ProjectionMatrix", camera.GetProjectionMatrix());
		//shader.SetUniformMat4f("u_ViewMatrix", camera.GetViewMatrix());
		shader.SetUniformMat4f("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
	}

	void Renderer::Draw(const Rectangle& rectangle)
	{
		//s_RenderData.VertexArray->AddBuffer(rectangle.GetVertexBuffer(), 0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
		//s_RenderData.VertexArray->AddBuffer(rectangle.GetVertexBuffer(), 1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 3 * sizeof(float));	
		

		std::vector<VertexData> vertices;
		vertices.reserve(4);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), rectangle.m_Position) * glm::scale(glm::mat4(1.0f), rectangle.m_Scale);

		
		// no as[ect ratio
		/*vertices.emplace_back(transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), rectangle.m_Color);
		vertices.emplace_back(transform * glm::vec4(rectangle.m_Size.x, 0.0f, 0.0f, 1.0f), rectangle.m_Color);
		vertices.emplace_back(transform * glm::vec4(rectangle.m_Size.x, rectangle.m_Size.y, 0.0f, 1.0f), rectangle.m_Color);
		vertices.emplace_back(transform * glm::vec4(0.0f, rectangle.m_Size.y, 0.0f, 1.0f), rectangle.m_Color);	*/	

		//  aspect ratio
		
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[0], rectangle.m_Color);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[1], rectangle.m_Color);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[2], rectangle.m_Color);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[3], rectangle.m_Color);
		
		s_RenderData.VertexBuffer->SetData(vertices);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 3 * sizeof(float));

		s_RenderData.VertexArray->Bind();
		s_RenderData.VertexBuffer->Bind();
		s_RenderData.IndexBuffer->Bind();		

		//shader.SetUniform4f("u_Color", m_Color);
		glDrawElements(GL_TRIANGLES, s_RenderData.IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
