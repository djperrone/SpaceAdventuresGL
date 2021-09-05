#include "sapch.h"
#include "Novaura/Core/Application.h"
#include "SpaceAdventures/SpaceAdventuresApp.h"

int main()
{
	Novaura::Application* app = new SpaceAdventures::SpaceAdventuresApp();
	
	while (app->IsRunning())
	{
		app->Update();
	}
	delete app;
	return 0;
}