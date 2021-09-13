#pragma once
#include "GameObjectData.h"

namespace SpaceAdventures {	
	class Asteroid;
	
	class Character;
	class Ship;
	class Projectile;

	class CollisionManager
	{
	public:
		CollisionManager(std::vector<std::shared_ptr<Character>>* characterList);
		CollisionManager();

		void Tick();
		bool IsColliding(Character* current, Character* other);	
		void HandleCollisionEvent(Character* current, Character* other);
		bool IsOnSameTeam(Character* current, Character* other);

	protected:

	private:
		std::vector<std::shared_ptr<Character>>* m_CharacterList;

	};
}