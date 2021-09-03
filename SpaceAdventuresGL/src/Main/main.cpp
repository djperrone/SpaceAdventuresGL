#include "sapch.h"
#include "Application.h"

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