#include "sapch.h"
#include "InputHandler.h"

#include "Novaura/Primitives/Rectangle.h"

namespace Novaura {
	
	std::shared_ptr<InputController> InputHandler::s_InputController;
	std::shared_ptr<Window> InputHandler::s_CurrentWindow;


	void InputHandler::Init()
	{		
		s_InputController = std::make_shared<InputController>();		
	}

	void InputHandler::Init(std::shared_ptr<InputController> controller)
	{
		//if (!s_Instance)
			//s_Instance = new InputHandler(controller);

	}

	void InputHandler::ShutDown()
	{
		//delete s_Instance;
	}

	InputHandler::InputHandler(std::shared_ptr<InputController> controller)
	{
		s_InputController = controller;
	}

	bool InputHandler::IsPressed(GLFWwindow* window, int keyCode)
	{
		return glfwGetKey(window, keyCode) == GLFW_PRESS;
	}

	bool InputHandler::IsPressed(int keyCode)
	{
		return glfwGetKey(GetCurrentWindow()->Window, keyCode) == GLFW_PRESS;
	}

	std::shared_ptr<InputController> InputHandler::CreateNewInputController()
	{
		//s_InputController.reset(new InputController());
		//return s_InputController;
		return std::make_shared<InputController>();
	}

	MousePosition InputHandler::GetMousePosition()
	{
		MousePosition mousePos;
		glfwGetCursorPos(GetCurrentWindow()->Window, &mousePos.x, &mousePos.y);
		return mousePos;
	}

	MousePosition InputHandler::GetMouseDeviceCoordinates()
	{		
		MousePosition mousePos;
		glfwGetCursorPos(GetCurrentWindow()->Window, &mousePos.x, &mousePos.y);

		mousePos.x = mousePos.x / GetCurrentWindow()->Width * GetCurrentWindow()->AspectRatio * 2.0f - GetCurrentWindow()->AspectRatio;
		mousePos.y =  1.0f - mousePos.y / GetCurrentWindow()->Height * 2.0f;
		return mousePos;
	}

	bool InputHandler::IsRectHovered(const Rectangle& rectangle)
	{
		struct Pos
		{
			float x, y;
		};
		auto [mx, my] = GetMouseDeviceCoordinates();

		Pos bottomLeft =	{ rectangle.GetPosition().x - rectangle.GetScale().x * 0.5f, rectangle.GetPosition().y - rectangle.GetScale().y * 0.5f };
		//Pos bottomRight =   { rectangle.m_Position.x + rectangle.m_Scale.x * 0.5f, rectangle.m_Position.y - rectangle.m_Scale.y * 0.5f };
		//Pos topLeft =		{ rectangle.m_Position.x - rectangle.m_Scale.x * 0.5f, rectangle.m_Position.y + rectangle.m_Scale.y * 0.5f };
		/* mx <= bottomRight.x && my >= bottomRight.y	&&
			 mx >= topLeft.x && my <= topLeft.y)*/
		Pos topRight =		{ rectangle.GetPosition().x + rectangle.GetScale().x * 0.5f, rectangle.GetPosition().y + rectangle.GetScale().y * 0.5f };

		if (mx >= bottomLeft.x && my >= bottomLeft.y &&	mx <= topRight.x && my <= topRight.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}