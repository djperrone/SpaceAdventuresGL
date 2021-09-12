#include "sapch.h"
#include "BatchRenderer.h"

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

	struct BatchRendererData
	{
		std::unique_ptr<VertexArray> VertexArray;
		std::unique_ptr<IndexBuffer> IndexBuffer;
		std::unique_ptr<VertexBuffer> VertexBuffer;

		std::unique_ptr<Shader> TextureShader;	

		glm::vec4 DefaultRectangleVertices[4];
		glm::vec2 DefaultTextureCoords[4];
		glm::vec2 NegativeTextureCoords = glm::vec2(-1.0f,-1.0f);

		static const uint32_t MaxRectangles = 10'000;
		static const uint32_t MaxVertices = MaxRectangles * 4;
		static const uint32_t MaxIndices = MaxRectangles * 6;

		std::vector<VertexData> RectBuffer;		
		
		static const uint32_t MaxTextures = 32;
		uint32_t CurrentTextureSlot = 1;
		std::array<std::shared_ptr<Texture>, MaxTextures> Textures;	
	};

	static BatchRendererData s_RenderData;

	void BatchRenderer::Init()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);

		//--------------------------------------------------------------------
		s_RenderData.VertexArray = std::make_unique<VertexArray>();
		s_RenderData.VertexBuffer = std::make_unique<VertexBuffer>();
		s_RenderData.TextureShader = std::make_unique<Shader>("Assets/Shaders/TextureShader.glsl");	

		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, Color));
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, TexCoord));
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, Quantity));
		s_RenderData.VertexArray->AddBuffer(*s_RenderData.VertexBuffer, 4, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), offsetof(VertexData, TextureSlot));
	
		
		s_RenderData.DefaultRectangleVertices[0] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
		s_RenderData.DefaultRectangleVertices[1] = glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
		s_RenderData.DefaultRectangleVertices[2] = glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
		s_RenderData.DefaultRectangleVertices[3] = glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);

		s_RenderData.DefaultTextureCoords[0] = glm::vec2(0.0f, 0.0f);
		s_RenderData.DefaultTextureCoords[1] = glm::vec2(1.0f, 0.0f);
		s_RenderData.DefaultTextureCoords[2] = glm::vec2(1.0f, 1.0f);
		s_RenderData.DefaultTextureCoords[3] = glm::vec2(0.0f, 1.0f);


		s_RenderData.RectBuffer.reserve(s_RenderData.MaxVertices * sizeof(VertexData));		

		std::vector<uint32_t> indices;
		indices.reserve(s_RenderData.MaxIndices);

		uint32_t offset = 0;
		for (auto i = 0; i < s_RenderData.MaxIndices; i += 6)
		{
			indices.emplace_back(0 + offset);
			indices.emplace_back(1 + offset);
			indices.emplace_back(2 + offset);
			indices.emplace_back(2 + offset);
			indices.emplace_back(3 + offset);
			indices.emplace_back(0 + offset);

			offset += 4;
		}		

		s_RenderData.IndexBuffer = std::make_unique <IndexBuffer>(&indices[0], s_RenderData.MaxIndices);		

		int32_t samplers[s_RenderData.MaxTextures];
		for (uint32_t i = 0; i < s_RenderData.MaxTextures; i++)
		{
			samplers[i] = i;
		}

		s_RenderData.TextureShader->Bind();
		s_RenderData.TextureShader->SetIntArray("u_Textures", samplers, s_RenderData.MaxTextures);
	}

	void BatchRenderer::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, 1.0f);
	}

	void BatchRenderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void BatchRenderer::BeginScene(const Camera& camera)
	{
		s_RenderData.TextureShader->Bind();
		
		s_RenderData.TextureShader->SetUniformMat4f("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());

		s_RenderData.VertexArray->Bind();
		s_RenderData.VertexBuffer->Bind();
		s_RenderData.IndexBuffer->Bind();
	}
	void BatchRenderer::EndScene()
	{				
		s_RenderData.VertexBuffer->SetData(s_RenderData.RectBuffer);		

		for (uint32_t i = 1; i < s_RenderData.CurrentTextureSlot; i++)
		{
			s_RenderData.Textures[i]->Bind(i);			
		}

		glDrawElements(GL_TRIANGLES, (s_RenderData.RectBuffer.size() / 4 * 6), GL_UNSIGNED_INT, nullptr);	

		s_RenderData.RectBuffer.clear();
		s_RenderData.CurrentTextureSlot = 1;
	}
	void BatchRenderer::DrawRectangle(const Rectangle& rectangle, const glm::vec2& quantity)
	{
		DrawRectangle(rectangle.GetPosition(), rectangle.GetScale(), rectangle.GetColor(), quantity);
	}
	void BatchRenderer::DrawRectangle(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color, const glm::vec2& quantity)
	{		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale);
		
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[0], color, s_RenderData.NegativeTextureCoords, quantity);
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[1], color, s_RenderData.NegativeTextureCoords, quantity);
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[2], color, s_RenderData.NegativeTextureCoords, quantity);
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[3], color, s_RenderData.NegativeTextureCoords, quantity);
	}
	void BatchRenderer::DrawRectangle(const Rectangle& rectangle, std::string_view texture, const glm::vec2& quantity)
	{
		DrawRectangle(rectangle.GetPosition(), rectangle.GetScale(), rectangle.GetColor(), texture, quantity);
	}
	void BatchRenderer::DrawRectangle(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color, std::string_view texture, const glm::vec2& quantity)
	{	
		auto tex = BatchTextureLoader::LoadTexture(texture);
		float texIndex = 0.0f;
		for (auto i = 1; i < s_RenderData.CurrentTextureSlot; i++)
		{
			if (s_RenderData.Textures[i]->GetTextureFile() == tex->GetTextureFile())
			{
				texIndex = static_cast<float>(i);
				break;
			}
		}
		if (texIndex == 0.0f)
		{
			texIndex = static_cast<float>(s_RenderData.CurrentTextureSlot);
			s_RenderData.Textures[s_RenderData.CurrentTextureSlot] = tex;			
			s_RenderData.CurrentTextureSlot++;
		}				

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale);

		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[0], color, s_RenderData.DefaultTextureCoords[0], glm::vec2(1.0f), texIndex);
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[1], color, s_RenderData.DefaultTextureCoords[1], glm::vec2(1.0f), texIndex);
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[2], color, s_RenderData.DefaultTextureCoords[2], glm::vec2(1.0f), texIndex);
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[3], color, s_RenderData.DefaultTextureCoords[3], glm::vec2(1.0f), texIndex);
	}
	void BatchRenderer::DrawRotatedRectangle(const Rectangle& rectangle, const glm::vec2& quantity)
	{
		DrawRotatedRectangle(rectangle.GetPosition(), rectangle.GetScale(), rectangle.GetRotation(), rectangle.GetColor(), quantity);
	}
	void BatchRenderer::DrawRotatedRectangle(const glm::vec3& position, const glm::vec3& scale, float rotation, const glm::vec4& color, const glm::vec2& quantity)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), scale);

		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[0], color, s_RenderData.NegativeTextureCoords, quantity);
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[1], color, s_RenderData.NegativeTextureCoords, quantity);
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[2], color, s_RenderData.NegativeTextureCoords, quantity);
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[3], color, s_RenderData.NegativeTextureCoords, quantity);
	}
	void BatchRenderer::DrawRotatedRectangle(const Rectangle& rectangle, std::string_view texture, const glm::vec2& quantity)
	{
		DrawRotatedRectangle(rectangle.GetPosition(), rectangle.GetScale(), rectangle.GetRotation(), rectangle.GetColor(), texture, quantity);

	}
	void BatchRenderer::DrawRotatedRectangle(const glm::vec3& position, const glm::vec3& scale, float rotation, const glm::vec4& color, std::string_view texture, const glm::vec2& quantity)
	{
		auto tex = BatchTextureLoader::LoadTexture(texture);
		float texIndex = 0.0f;
		for (auto i = 1; i < s_RenderData.CurrentTextureSlot; i++)
		{
			if (s_RenderData.Textures[i]->GetTextureFile() == tex->GetTextureFile())
			{
				texIndex = static_cast<float>(i);
				break;
			}
		}
		if (texIndex == 0.0f)
		{
			texIndex = static_cast<float>(s_RenderData.CurrentTextureSlot);
			s_RenderData.Textures[s_RenderData.CurrentTextureSlot] = tex;			
			s_RenderData.CurrentTextureSlot++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), scale);

		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[0], color, s_RenderData.DefaultTextureCoords[0], glm::vec2(1.0f), texIndex);
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[1], color, s_RenderData.DefaultTextureCoords[1], glm::vec2(1.0f), texIndex);
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[2], color, s_RenderData.DefaultTextureCoords[2], glm::vec2(1.0f), texIndex);
		s_RenderData.RectBuffer.emplace_back(transform * s_RenderData.DefaultRectangleVertices[3], color, s_RenderData.DefaultTextureCoords[3], glm::vec2(1.0f), texIndex);
	}
}