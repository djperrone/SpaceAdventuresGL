#include "sapch.h"
#include "CollisionManager.h"
#include "SpaceAdventures/Actors/Character.h"
#include "SpaceAdventures/GamePlay/GameObjects/Asteroid.h"
#include "SpaceAdventures/GamePlay/GameObjects/SpaceShip.h"
#include "SpaceAdventures/GamePlay/GameObjects/Projectile.h"

namespace SpaceAdventures {

	CollisionManager::CollisionManager(std::vector<std::shared_ptr<Character>>* characterList)
		: m_CharacterList(characterList)
	{
		
	}

	

	void CollisionManager::Tick()
	{

		for (auto& current : *m_CharacterList)
		{
			if (current->IsCollidable())
			{
				for (auto& other : *m_CharacterList)
				{
					if (other->IsCollidable())
					{
						if (IsColliding(current.get(), other.get()) && !IsOnSameTeam(current.get(), other.get()))
						{
							HandleCollisionEvent(current.get(), other.get());
						}
					}					
				}
			}			
		}		
	}

	void CollisionManager::HandleCollisionEvent(Character* current, Character* other)
	{
		//std::cout << "collission detected!\n";
		current->Attack(other);
		//other->Attack(current);
	}

	bool CollisionManager::IsOnSameTeam(Character* current, Character* other)
	{
		//std::cout << "current team: " << static_cast<std::size_t>(current->GetTeam()) << ", other team: " << static_cast<std::size_t>(other->GetTeam()) << std::endl;
		return current->GetTeam() == other->GetTeam();
	}


	bool CollisionManager::IsColliding(Character* current, Character* other)
	{
		Bounds boundsA = current->GetBounds();
		Bounds boundsB = other->GetBounds();

		if (boundsA.BottomRight.x >= boundsB.BottomLeft.x &&
			boundsB.BottomRight.x >= boundsA.BottomLeft.x &&
			boundsA.TopLeft.y >= boundsB.BottomRight.y		  &&
			boundsB.TopRight.y >= boundsA.BottomLeft.y)
		{
			//spdlog::info(__FUNCTION__);

			return true;
		}

		return false;
	}


}