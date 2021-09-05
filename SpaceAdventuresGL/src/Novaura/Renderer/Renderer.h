#pragma once

#include "Novaura/Renderer/IndexBuffer.h"
#include "Novaura/Renderer/VertexArray.h"
#include "Novaura/Renderer/VertexBuffer.h"

#include "Novaura/Primitives/Rectangle.h"
#include "Novaura/Camera/Camera.h"

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
		static void DrawRotatedRectangle(const Rectangle& rectangle);
	
	};
}