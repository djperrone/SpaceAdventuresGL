#include "sapch.h"
#include "OpenGLContext.h"

#include <spdlog/spdlog.h>

OpenGLContext* OpenGLContext::GLFWCallbackWrapper::s_Application = nullptr;


OpenGLContext::OpenGLContext(float width, float height)
{
    // glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_Window.Width = width;
    m_Window.Height = height;
    m_Window.AspectRatio = m_Window.Width / m_Window.Height;
    m_Window.Window = glfwCreateWindow(m_Window.Width, m_Window.Height, "LearnOpenGL", NULL, NULL);
    if (m_Window.Window == NULL)
    {
        spdlog::error("Failed to create GLFW window");
        glfwTerminate();

        exit(0);
    }
    glfwMakeContextCurrent(m_Window.Window);

    // glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        spdlog::error("Failed to initialize GLAD");
        exit(0);
    }

    glViewport(0, 0, m_Window.Width, m_Window.Height);
    SetCallBackFunctions();


    spdlog::info("glfw initialized");

}
void OpenGLContext::SwapBuffers() const
{
    glfwSwapBuffers(m_Window.Window);
}

bool OpenGLContext::IsRunning() const
{
    return !glfwWindowShouldClose(m_Window.Window);
}

OpenGLContext::~OpenGLContext()
{
    glfwTerminate();

}

void OpenGLContext::PollEvents()
{
    glfwPollEvents();
}

void OpenGLContext::SetCallBackFunctions()
{
    GLFWCallbackWrapper::SetApplication(this);
    //glfwSetCursorPosCallback(m_Window.Window, GLFWCallbackWrapper::MousePositionCallback);
   // glfwSetScrollCallback(m_Window.Window, GLFWCallbackWrapper::MouseScrollCallBack);
    glfwSetFramebufferSizeCallback(m_Window.Window, GLFWCallbackWrapper::WindowResizeCallBack);
}

void OpenGLContext::GLFWCallbackWrapper::SetApplication(OpenGLContext* application)
{
    GLFWCallbackWrapper::s_Application = application;
}


void OpenGLContext::GLFWCallbackWrapper::WindowResizeCallBack(GLFWwindow* window, int width, int height)
{
    s_Application->WindowResizeCallBack(window, width, height);
}

void OpenGLContext::WindowResizeCallBack(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    m_Window.Width = width;
    m_Window.Height = height;
}