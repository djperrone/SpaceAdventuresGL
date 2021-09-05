#include "sapch.h"
#include "glfwCallBackWrapper.h"
#include "Application.h"
namespace Nova {

    Application* GLFWCallbackWrapper::s_Application = nullptr;

    void GLFWCallbackWrapper::SetApplication(Application* application)
    {
        GLFWCallbackWrapper::s_Application = application;
    }

    void GLFWCallbackWrapper::MouseScrollCallBack(GLFWwindow* window, double xOffset, double yOffset)
    {
        s_Application->MouseScrollCallBack(xOffset, yOffset);
    }

    


    void GLFWCallbackWrapper::WindowResizeCallBack(GLFWwindow* window, int width, int height)
    {
        s_Application->WindowResizeCallBack(width, height);

    }
}