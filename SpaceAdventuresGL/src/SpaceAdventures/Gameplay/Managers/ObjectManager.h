#pragma once


#include "Spawner.h"

#include "../GameObjects/Asteroid.h"
#include "../GameObjects/Player.h"

#include "SpaceAdventures/Actors/Character.h"
#include "SpaceAdventures/GamePlay/GameObjects/SpaceShip.h"
#include "SpaceAdventures/Gameplay/Managers/CollisionManager.h"

#include "ProjectileManager.h"
#include "GameObjectData.h"

namespace SpaceAdventures {	

	class ObjectManager
	{
	public:
		ObjectManager();		
		void Update(float dt);
		void CleanList();
		void LoadAllProjectiles();

		bool IsWithinBounds(const Character& object);
		inline Player& GetPlayer() { return *m_Player; }

	public:
		//static const uint32_t MAX_CHARACTERS = 200;

		std::vector<std::shared_ptr<Character>>& GetCharacterList() { return m_CharacterList; }
		const std::vector<std::shared_ptr<Ship>>& GetShipList() const { return m_Spawner->GetShipList(); }
		//std::list<std::shared_ptr<Character>>& GetProjectileList() { return m_ProjectileList; }

	private:
		std::unique_ptr<CollisionManager> m_CollisionManager;

	private:
	
		std::shared_ptr<Player> m_Player;			
		std::unique_ptr<Character> m_MouseController;
		std::unique_ptr<Spawner> m_Spawner;
		
		//std::list<std::shared_ptr<Character>> m_ObjectList;
		//std::list<std::shared_ptr<Character>> m_ProjectileList;
		//std::list<std::shared_ptr<Ship>> m_ShipList;
		//std::list<std::unique_ptr<Asteroid>> m_AsteroidList;

		

		std::vector<std::shared_ptr<Character>> m_CharacterList;
		
		//uint32_t currentSpawnSlot;

		std::unique_ptr<ProjectileManager> m_ProjectileManager;
	};
}