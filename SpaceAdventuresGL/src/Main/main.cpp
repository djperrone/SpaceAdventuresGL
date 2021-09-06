#include "sapch.h"
#include "Novaura/Core/Application.h"
#include "SpaceAdventures/SpaceAdventuresApp.h"

int main()
{
	Novaura::Application* app = new SpaceAdventures::SpaceAdventuresApp("Space Adventures", 1280.0f, 720.0f);
	
	while (app->IsRunning())
	{
		app->Update();
	}
	delete app;
	return 0;
}