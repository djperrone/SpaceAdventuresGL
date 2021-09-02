#pragma once
#include "OpenGLContext.h"
#include "Primitives/Rectangle.h"
#include "Renderer/Shader.h"

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

	std::unique_ptr<Rectangle> m_Rect;
	std::unique_ptr<Shader> m_Shader;
};