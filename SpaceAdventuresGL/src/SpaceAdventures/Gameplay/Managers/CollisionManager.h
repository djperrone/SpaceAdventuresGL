#pragma once

namespace SpaceAdventures {	
	class Asteroid;
	
	class Character;
	class Ship;
	class Projectile;

	class CollisionManager
	{
	public:
		CollisionManager(std::list<std::shared_ptr<Ship>>* objList, std::list<std::unique_ptr<Asteroid>>* asteroidList, std::list<std::shared_ptr<Character>>* projectileList);
		CollisionManager();

		void Tick();
		bool IsColliding(Character* current, Character* other);	
		void HandleCollisionEvent(Character* current, Character* other);
		bool IsOnSameTeam(Character* current, Character* other);

	protected:

	private:
		std::list<std::shared_ptr<Ship>>* m_ShipList;
		std::list<std::unique_ptr<Asteroid>>* m_AsteroidList;
		std::list<std::shared_ptr<Character>>* m_ProjectileList;		
	};
}