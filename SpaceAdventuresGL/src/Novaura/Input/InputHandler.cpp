#include "sapch.h"
#include "InputHandler.h"



namespace Novaura {

	//InputHandler* InputHandler::s_Instance;
	/*std::unordered_map<int, Command> InputHandler::AxisKeyBindings;
	std::unordered_map<EventType, std::unordered_map<KeyCode, Command>> InputHandler::ActionKeyBindings;*/
	std::shared_ptr<InputController> InputHandler::s_InputController;
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

}