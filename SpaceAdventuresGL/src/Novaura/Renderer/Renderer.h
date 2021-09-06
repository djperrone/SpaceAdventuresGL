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
		static void DrawRectangle(const Rectangle& rectangle);
		static void DrawRectangle(const Rectangle& rectangle, std::string_view texture);
		static void DrawRotatedRectangle(const Rectangle& rectangle);
		static void DrawRotatedRectangle(const Rectangle& rectangle, std::string_view texture);
	
	};
}