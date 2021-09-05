#pragma once
#include <GLFW/glfw3.h>
#include <queue>
#include "Command.h"
#include "InputController.h"

namespace Novaura {	

	using EventType = int;
	using KeyCode = int;

	struct Event
	{
		EventType Type;
		KeyCode Key;
	};

	class InputHandler
	{
	public:
		
		static void Init();
		static void ShutDown();
		static bool IsPressed(GLFWwindow* window, int keyCode);

		static void SetCurrentController(std::shared_ptr<InputController> controller) { s_InputController = controller; }
		static InputController& GetCurrentController() { return *s_InputController; }
		

		//static std::queue<Event> EventQueue;
	private:
		static std::shared_ptr<InputController> s_InputController;

	private:
		static InputHandler* s_Instance;
	};
}
