#pragma once

namespace Core {

	class Renderer
	{
	public:		
		Renderer() = default;
		static void Init();
		static void Clear();
		static void SetClearColor(float r, float g, float b, float a = 1.0f);

		// static void Draw();
	private:

	};
}