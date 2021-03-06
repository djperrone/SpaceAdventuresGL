#pragma once

#include "Novaura/Primitives/Rectangle.h"
#include "Novaura/Camera/Camera.h"
#include "Novaura/Renderer/Shader.h"


namespace Novaura {

	class Renderer
	{
	public:		
		Renderer() = default;
		static void Init();
		static void Init(const Camera& camera);
		static void Clear();
		static void SetClearColor(float r, float g, float b, float a = 1.0f);

		static void BeginScene(Shader& shader, const Camera& camera);
		static void BeginScene(const Camera& camera);
		static void DrawRectangle(const Rectangle& rectangle, const glm::vec2& quantity = { 1.0f,1.0f });
		static void DrawRectangle(const Rectangle& rectangle, std::string_view texture, const glm::vec2& quantity = { 1.0f,1.0f });


		static void DrawRotatedRectangle(const Rectangle& rectangle, const glm::vec2& quantity = { 1.0f,1.0f });
		static void DrawRotatedRectangle(const Rectangle& rectangle, std::string_view texture, const glm::vec2& quantity = { 1.0f,1.0f });

	


		static void DrawRectangle(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color, const glm::vec2& quantity = { 1.0f,1.0f });
		static void DrawRectangle(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color, std::string_view texture, const glm::vec2& quantity = { 1.0f,1.0f });



		static void DrawRotatedRectangle(const glm::vec3& position, const glm::vec3& scale, float rotation, const glm::vec4& color, const glm::vec2& quantity = { 1.0f,1.0f });
		static void DrawRotatedRectangle(const glm::vec3& position, const glm::vec3& scale, float rotation, const glm::vec4& color, std::string_view texture, const glm::vec2& quantity = { 1.0f,1.0f });
		static void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

	};
}