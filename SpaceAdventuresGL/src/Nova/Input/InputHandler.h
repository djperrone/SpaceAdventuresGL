#pragma once
#include <GLFW/glfw3.h>
#include <queue>
#include "Command.h"

namespace Nova {	

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

		template <typename... T>
		static void BindAxisKeyEvent(KeyCode code, T&&... args)
		{
			AxisKeyBindings[code] = Command(std::bind(args...));
		}
		template <typename... T>
		static void BindActionKeyEvent(EventType action, KeyCode code, T&&... args)
		{
			ActionKeyBindings[action][code] = Command(std::bind(args...));
		}

		//static std::queue<Event> EventQueue;
		static std::unordered_map<int, Command> AxisKeyBindings;
		//std::unordered_map<int, Command> ActionKeyBindings;
		static std::unordered_map<EventType, std::unordered_map<KeyCode, Command>> ActionKeyBindings;
	private:
		static InputHandler* s_Instance;
	};
}
