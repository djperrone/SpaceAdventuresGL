#include "sapch.h"
#include "InputHandler.h"



namespace Novaura {

	InputHandler* InputHandler::s_Instance = nullptr;
	/*std::unordered_map<int, Command> InputHandler::AxisKeyBindings;
	std::unordered_map<EventType, std::unordered_map<KeyCode, Command>> InputHandler::ActionKeyBindings;*/
	std::shared_ptr<InputController> InputHandler::s_InputController;
	void InputHandler::Init()
	{
		if (!s_Instance)
			s_Instance = new InputHandler();
	}

	void InputHandler::ShutDown()
	{
		delete s_Instance;
	}

	bool InputHandler::IsPressed(GLFWwindow* window, int keyCode)
	{
		return glfwGetKey(window, keyCode) == GLFW_PRESS;
	}

}