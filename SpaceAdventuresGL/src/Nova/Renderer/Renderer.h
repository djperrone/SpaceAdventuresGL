#pragma once

#include "Nova/Renderer/IndexBuffer.h"
#include "Nova/Renderer/VertexArray.h"
#include "Nova/Renderer/VertexBuffer.h"

#include "Nova/Primitives/Rectangle.h"
#include "Nova/Camera/Camera.h"

namespace Nova {

	class Renderer
	{
	public:		
		Renderer() = default;
		static void Init();
		static void Clear();
		static void SetClearColor(float r, float g, float b, float a = 1.0f);

		static void BeginScene(Shader& shader, const Camera& camera);
		static void Draw(const Rectangle& rectangle);
	
	};
}