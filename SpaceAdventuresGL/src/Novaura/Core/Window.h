#pragma once
#include <GLFW/glfw3.h>

struct Window
{
	GLFWwindow* Window;
	float Width = 800.0f;
	float Height = 600.0f;
	float AspectRatio = Width / Height;
};