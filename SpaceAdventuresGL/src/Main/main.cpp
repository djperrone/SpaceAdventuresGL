#include "sapch.h"
#include "Novaura/Core/Application.h"

int main()
{
	Novaura::Application* app = new Novaura::Application();
	while (app->IsRunning())
	{
		app->Update();
	}
	delete app;
	return 0;
}