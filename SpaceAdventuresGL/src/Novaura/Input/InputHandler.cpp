#include "sapch.h"
#include "InputHandler.h"

#include "Novaura/Primitives/Rectangle.h"

namespace Novaura {

	//InputHandler* InputHandler::s_Instance;
	/*std::unordered_map<int, Command> InputHandler::AxisKeyBindings;
	std::unordered_map<EventType, std::unordered_map<KeyCode, Command>> InputHandler::ActionKeyBindings;*/
	std::shared_ptr<InputController> InputHandler::s_InputController;
	std::shared_ptr<Window> InputHandler::s_CurrentWindow;

	void InputHandler::Init()
	{
		//if (!s_Instance)
		//{
			//s_Instance = new InputHandler();
			s_InputController = std::make_shared<InputController>();
		//}
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

	MousePosition InputHandler::GetMousePosition()
	{
		MousePosition mousePos;
		glfwGetCursorPos(GetCurrentWindow()->Window, &mousePos.x, &mousePos.y);
		return mousePos;
	}

	bool InputHandler::IsRectClicked(const Rectangle& rectangle)
	{
		return false;
	}

}