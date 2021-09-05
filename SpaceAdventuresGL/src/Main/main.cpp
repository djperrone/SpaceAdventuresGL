#include "sapch.h"
#include "Nova/Core/Application.h"

int main()
{
	Nova::Application* app = new Nova::Application();
	while (app->IsRunning())
	{
		app->Update();
	}
	delete app;
	return 0;
}