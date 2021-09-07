#pragma once


#include "Spawner.h"
//#include "CollisionManager.h"
//#include "ProjectileManager.h"
#include "../GameObjects/Asteroid.h"
#include "../GameObjects/Player.h"
//#include "InputHandler/InputController.h"

#include "SpaceAdventures/Actors/Character.h"
#include "SpaceAdventures/GamePlay/GameObjects/SpaceShip.h"

#include "ProjectileManager.h"
#include "SpaceAdventures/Gameplay/Managers/CollisionManager.h"


namespace SpaceAdventures {


	class ObjectManager
	{
	public:
		ObjectManager();
		//void Render(std::shared_ptr<Renderer>& renderer);	
		void Update(float dt);
		void CleanList();
		void LoadAllProjectiles();

		bool IsWithinBounds(const Character& object);
		inline Player& GetPlayer() { return *m_Player; }

		std::list<std::unique_ptr<Asteroid>>& GetAsteroidList() { return m_AsteroidList; }
		std::list<std::shared_ptr<Ship>>& GetShipList() { return m_ShipList; }
		std::list<std::shared_ptr<Character>>& GetProjectileList() { return m_ProjectileList; }

	private:
		std::unique_ptr<CollisionManager> m_CollisionManager;


	private:
		//std::unique_ptr<CollisionManager> m_CollisionManager;
		std::shared_ptr<Player> m_Player;	
		//std::unique_ptr<KeyboardController> m_InputController;
		std::unique_ptr<Character> m_MouseController;
		std::unique_ptr<Spawner> m_Spawner;
		//Dimensions dimensions;
		std::list<std::shared_ptr<Character>> m_ObjectList;
		std::list<std::shared_ptr<Character>> m_ProjectileList;
		std::list <std::shared_ptr<Ship>> m_ShipList;
		std::list <std::unique_ptr<Asteroid>> m_AsteroidList;

		std::unique_ptr<ProjectileManager> m_ProjectileManager;
		//std::unique_ptr<Character> m_ReloadIcon;

		//bool isFirst;

	};

}