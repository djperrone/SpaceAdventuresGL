#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace SpaceAdventures {

	class MovementComponent : public Component
	{
	public:
		COMPONENT_CLASS_TYPE(MovementComponent)

		MovementComponent();
		MovementComponent(const glm::vec2& velocity, float speed);

		virtual ~MovementComponent();

		float GetSpeed();
		void SetSpeed(float speed);

		glm::vec2 GetVelocity();	
		void SetVelocity(const glm::vec2& velocity);		

	private:
		glm::vec2 m_Velocity;
		float m_Speed;
	};

}