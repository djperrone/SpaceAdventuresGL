#pragma once
#include <GLFW/glfw3.h>

namespace Nova {

	class Application;

	class GLFWCallbackWrapper
	{
	public:
		GLFWCallbackWrapper() = delete;
		GLFWCallbackWrapper(const GLFWCallbackWrapper&) = delete;
		GLFWCallbackWrapper(GLFWCallbackWrapper&&) = delete;
		~GLFWCallbackWrapper() = delete;

		static void WindowResizeCallBack(GLFWwindow* window, int width, int height);
		static void MousePositionCallback(GLFWwindow* window, double positionX, double positionY);
		static void MouseScrollCallBack(GLFWwindow* window, double xOffset, double yOffset);
		static void SetApplication(Application* application);
	private:
		static Application* s_Application;
	};
}