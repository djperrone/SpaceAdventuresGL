#pragma once
#include "SpaceAdventures/Gameplay/GameObjects/SpaceShip.h"

namespace SpaceAdventures {

	class Player : public Ship
	{
	public:
		Player();
		~Player() = default;
		//Player(glm::vec2 pos);
		//Player(float x, float y);

		virtual void FireGun() override;
		virtual void Update(float dt) override;

		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();
		bool Reload();

	private:		
		float m_DeltaTime;
		glm::vec2 m_PreviousPosition;
	};
}