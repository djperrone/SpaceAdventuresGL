#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"

namespace Novaura {

	class OpenGLContext
	{
	public:
		OpenGLContext(float width, float height);
		~OpenGLContext();
	
		void PollEvents();
	
		Window& GetWindow() { return m_Window; }
		const Window& GetWindow() const { return m_Window; }
	
		void SwapBuffers() const;
		bool OpenGLContext::IsRunning() const;
	
	
	private:
		Window m_Window;
	
	private:
		void SetCallBackFunctions();
	
		void WindowResizeCallBack(GLFWwindow* window, int width, int height);
	
	private:
		/*class GLFWCallbackWrapper
		{
		public:
			GLFWCallbackWrapper() = delete;
			GLFWCallbackWrapper(const GLFWCallbackWrapper&) = delete;
			GLFWCallbackWrapper(GLFWCallbackWrapper&&) = delete;
			~GLFWCallbackWrapper() = delete;
	
			static void WindowResizeCallBack(GLFWwindow* window, int width, int height);
			static void MousePositionCallback(GLFWwindow* window, double positionX, double positionY);
			static void MouseScrollCallBack(GLFWwindow* window, double xOffset, double yOffset);
			static void SetApplication(OpenGLContext* application);
		private:
			static OpenGLContext* s_Application;
		};*/
	
	};
}
