#pragma once
#include "Nova/Core/OpenGLContext.h"
#include "Nova/Primitives/Rectangle.h"
#include "Nova/Renderer/Shader.h"
#include "Nova/Camera/Camera.h"

namespace Nova {

	class Application
	{
	public:
		Application();

		void Update();
		void BeginFrame();
		void EndFrame();

		inline bool IsRunning() const { return m_Context.IsRunning(); }


	private:
		OpenGLContext m_Context;
		Camera m_Camera;

		std::unique_ptr<Rectangle> m_Rect;
		std::unique_ptr<Shader> m_Shader;
	};
}