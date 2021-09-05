#pragma once
#include "Novaura/Core/OpenGLContext.h"
#include "Novaura/Primitives/Rectangle.h"
#include "Novaura/Renderer/Shader.h"
#include "Novaura/Camera/Camera.h"
#include "Novaura/Camera/CameraController.h"

#include "Novaura/Input/InputController.h"

namespace Novaura {

	class Application
	{
	public:
		Application();

		void Update();
		void BeginFrame();
		void EndFrame();
		const Window& GetWindow() const { return m_Context.GetWindow(); }
		Window& GetWindow() { return m_Context.GetWindow(); }
		inline bool IsRunning() const { return m_Context.IsRunning(); }
		void ScreenSaver();
	public:
		void SetCallBackFunctions();

		void WindowResizeCallBack(int width, int height);
		void KeyboardCallback(int key, int scancode, int action, int mods);
		
		void MousePositionCallBack(double positionX, double positionY);
		void MouseButtonCallBack(int button, int action, int mods);
		void MouseScrollCallBack(double xoffset, double yoffset);

	public:
		std::shared_ptr<InputController> m_InputController;


	private:
		OpenGLContext m_Context;
		Camera m_Camera;
		CameraController m_CameraController;
		std::unique_ptr<Rectangle> m_Rect;
		std::unique_ptr<Shader> m_Shader;

	private:
		float m_DeltaTime = 0.0f;
		float m_LastFrame = 0.0f;

	};
}