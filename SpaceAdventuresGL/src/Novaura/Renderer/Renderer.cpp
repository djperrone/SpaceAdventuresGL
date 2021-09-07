#include "sapch.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <spdlog/spdlog.h>

#include "Novaura/Renderer/TextureLoader.h"
#include "Novaura/Renderer/Vertex.h"
#include "Novaura/Renderer/IndexBuffer.h"
#include "Novaura/Renderer/VertexArray.h"
#include "Novaura/Renderer/VertexBuffer.h"

namespace Novaura {

	struct RenderData
	{	
		std::unique_ptr<VertexArray> VertexArray;
		std::unique_ptr<IndexBuffer> IndexBuffer;
		std::unique_ptr<VertexBuffer> VertexBuffer;

		std::unique_ptr<Shader> TextureShader;
		std::unique_ptr<Shader> ColorShader;

		glm::vec4 DefaultRectangleVertices[4];
		glm::vec2 DefaultTextureCoords[4];
	};

	const Camera* SceneCamera = nullptr;

	static RenderData s_RenderData;

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, 1.0f);
	}	

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Renderer::Init()
	{
		//glEnable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		

		SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);

		s_RenderData.VertexArray = std::make_unique<VertexArray>();
		s_RenderData.VertexBuffer = std::make_unique<VertexBuffer>();
		s_RenderData.TextureShader = std::make_unique<Shader>("Assets/Shaders/TextureShader.glsl");
		s_RenderData.ColorShader = std::make_unique<Shader>("Assets/Shaders/BasicColorShader.glsl");

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

		s_RenderData.DefaultTextureCoords[0] = glm::vec2(0.0f, 0.0f);
		s_RenderData.DefaultTextureCoords[1] = glm::vec2(1.0f, 0.0f);
		s_RenderData.DefaultTextureCoords[2] = glm::vec2(1.0f, 1.0f);
		s_RenderData.DefaultTextureCoords[3] = glm::vec2(0.0f, 1.0f);
	}

	void Renderer::Init(const Camera& camera)
	{
	}
	
	void Renderer::BeginScene(Shader& shader, const Camera& camera)
	{
		//SceneCamera = &camera;
		shader.Bind();
		
		//shader.SetUniformMat4f("u_ProjectionMatrix", camera.GetProjectionMatrix());
		//shader.SetUniformMat4f("u_ViewMatrix", camera.GetViewMatrix());
		shader.SetUniformMat4f("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		s_RenderData.ColorShader->Bind();
		s_RenderData.ColorShader->SetUniformMat4f("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());

		s_RenderData.TextureShader->Bind();		
		s_RenderData.TextureShader->SetUniformMat4f("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());



	}

	void Renderer::DrawRectangle(const Rectangle& rectangle)
	{		

		std::vector<VertexData> vertices;
		vertices.reserve(4);
		s_RenderData.TextureShader->SetUniform1f("u_Quantity", 1.0f);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), rectangle.GetPosition()) * glm::scale(glm::mat4(1.0f), rectangle.GetScale());		
		

		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[0], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[0]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[1], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[1]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[2], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[2]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[3], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[3]);
		
		s_RenderData.VertexBuffer->SetData(vertices);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, Color));
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, TexCoord));

		s_RenderData.VertexArray->Bind();
		s_RenderData.VertexBuffer->Bind();
		s_RenderData.IndexBuffer->Bind();		

		//shader.SetUniform4f("u_Color", m_Color);
		glDrawElements(GL_TRIANGLES, s_RenderData.IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Renderer::DrawRectangle(const Rectangle& rectangle, std::string_view texture)
	{
		Texture tex = TextureLoader::LoadTexture(texture);
		tex.Bind();
		s_RenderData.TextureShader->SetUniform1f("u_Quantity", 1.0f);

		std::vector<VertexData> vertices;
		vertices.reserve(4);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), rectangle.GetPosition()) * glm::scale(glm::mat4(1.0f), rectangle.GetScale());


		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[0], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[0]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[1], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[1]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[2], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[2]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[3], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[3]);

		s_RenderData.VertexBuffer->SetData(vertices);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, Color));
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, TexCoord));

		s_RenderData.VertexArray->Bind();
		s_RenderData.VertexBuffer->Bind();
		s_RenderData.IndexBuffer->Bind();

		//shader.SetUniform4f("u_Color", m_Color);
		glDrawElements(GL_TRIANGLES, s_RenderData.IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		tex.UnBind();

	}
	void Renderer::DrawRotatedRectangle(const Rectangle& rectangle)
	{
		std::vector<VertexData> vertices;
		vertices.reserve(4);
		s_RenderData.TextureShader->SetUniform1f("u_Quantity", 1.0f);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), rectangle.GetPosition())
			* glm::rotate(glm::mat4(1.0f), glm::radians(rectangle.GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), rectangle.GetScale());		

		/*auto test = transform * s_RenderData.DefaultRectangleVertices[0];
		spdlog::info("first {0}, {1}", test.x, test.y);
		test = transform * s_RenderData.DefaultRectangleVertices[1];
		spdlog::info("{0}, {1}", test.x, test.y);
		test = transform * s_RenderData.DefaultRectangleVertices[2];
		spdlog::info("{0}, {1}", test.x, test.y);
		test = transform * s_RenderData.DefaultRectangleVertices[3];
		spdlog::info("last {0}, {1}", test.x, test.y);*/


		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[0], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[0]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[1], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[1]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[2], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[2]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[3], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[3]);

		s_RenderData.VertexBuffer->SetData(vertices);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, Color));
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, TexCoord));

		s_RenderData.VertexArray->Bind();
		s_RenderData.VertexBuffer->Bind();
		s_RenderData.IndexBuffer->Bind();

		//shader.SetUniform4f("u_Color", m_Color);
		glDrawElements(GL_TRIANGLES, s_RenderData.IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Renderer::DrawRotatedRectangle(const Rectangle& rectangle, std::string_view texture)
	{
		Texture tex = TextureLoader::LoadTexture(texture);
		s_RenderData.TextureShader->SetUniform1f("u_Quantity", 1.0f);

		tex.Bind();

		std::vector<VertexData> vertices;
		vertices.reserve(4);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), rectangle.GetPosition())
			* glm::rotate(glm::mat4(1.0f), glm::radians(rectangle.GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), rectangle.GetScale());

		


		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[0], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[0]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[1], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[1]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[2], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[2]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[3], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[3]);

		s_RenderData.VertexBuffer->SetData(vertices);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, Color));
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, TexCoord));

		s_RenderData.VertexArray->Bind();
		s_RenderData.VertexBuffer->Bind();
		s_RenderData.IndexBuffer->Bind();

		//shader.SetUniform4f("u_Color", m_Color);
		glDrawElements(GL_TRIANGLES, s_RenderData.IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		tex.UnBind();

	}

	void Renderer::DrawTiledRect(const Rectangle& rectangle, std::string_view texture, float quantity)
	{
		Texture tex = TextureLoader::LoadTexture(texture);
		tex.Bind();

		s_RenderData.TextureShader->SetUniform1f("u_Quantity", quantity);

		std::vector<VertexData> vertices;
		vertices.reserve(4);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), rectangle.GetPosition()) * glm::scale(glm::mat4(1.0f), rectangle.GetScale());


		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[0], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[0]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[1], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[1]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[2], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[2]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[3], rectangle.GetColor(), s_RenderData.DefaultTextureCoords[3]);

		s_RenderData.VertexBuffer->SetData(vertices);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, Color));
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, TexCoord));

		s_RenderData.VertexArray->Bind();
		s_RenderData.VertexBuffer->Bind();
		s_RenderData.IndexBuffer->Bind();

		//shader.SetUniform4f("u_Color", m_Color);
		glDrawElements(GL_TRIANGLES, s_RenderData.IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		tex.UnBind();
	}

	void Renderer::DrawRectangle(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color, float quantity)
	{
		s_RenderData.ColorShader->Bind();
		//s_RenderData.TextureShader->SetUniform1f("u_Quantity", quantity);
		s_RenderData.ColorShader->SetUniform1f("u_Quantity", quantity);


		std::vector<VertexData> vertices;
		vertices.reserve(4);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale);


		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[0], color, s_RenderData.DefaultTextureCoords[0]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[1], color, s_RenderData.DefaultTextureCoords[1]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[2], color, s_RenderData.DefaultTextureCoords[2]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[3], color, s_RenderData.DefaultTextureCoords[3]);

		s_RenderData.VertexBuffer->SetData(vertices);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, Color));
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, TexCoord));

		s_RenderData.VertexArray->Bind();
		s_RenderData.VertexBuffer->Bind();
		s_RenderData.IndexBuffer->Bind();

		//shader.SetUniform4f("u_Color", m_Color);
		glDrawElements(GL_TRIANGLES, s_RenderData.IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		s_RenderData.TextureShader->Bind();

	}

	void Renderer::DrawRectangle(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color, std::string_view texture, float quantity)
	{
		Texture tex = TextureLoader::LoadTexture(texture);
		tex.Bind();
		s_RenderData.TextureShader->SetUniform1f("u_Quantity", quantity);

		std::vector<VertexData> vertices;
		vertices.reserve(4);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale);


		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[0], color, s_RenderData.DefaultTextureCoords[0]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[1], color, s_RenderData.DefaultTextureCoords[1]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[2], color, s_RenderData.DefaultTextureCoords[2]);
		vertices.emplace_back(transform * s_RenderData.DefaultRectangleVertices[3], color, s_RenderData.DefaultTextureCoords[3]);

		s_RenderData.VertexBuffer->SetData(vertices);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, Color));
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, TexCoord));

		s_RenderData.VertexArray->Bind();
		s_RenderData.VertexBuffer->Bind();
		s_RenderData.IndexBuffer->Bind();

		//shader.SetUniform4f("u_Color", m_Color);
		glDrawElements(GL_TRIANGLES, s_RenderData.IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		tex.UnBind();
	}

	void Renderer::DrawRotatedRectangle(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color, std::string_view texture)
	{
	}

}
