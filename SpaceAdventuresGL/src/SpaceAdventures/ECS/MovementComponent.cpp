#include "sapch.h"
#include "MovementComponent.h"

namespace SpaceAdventures {

	MovementComponent::MovementComponent()
	{
	}

	MovementComponent::MovementComponent(const glm::vec2& velocity, float speed)
		: m_Velocity(velocity), m_Speed(speed)
	{
	}

	MovementComponent::~MovementComponent()
	{
	}

	float MovementComponent::GetSpeed()
	{
		return m_Speed;
	}

	void MovementComponent::SetSpeed(float speed)
	{
		m_Speed = speed;
	}

	glm::vec2 MovementComponent::GetVelocity()
	{
		return m_Velocity;
	}	

	void MovementComponent::SetVelocity(const glm::vec2& velocity)
	{
		m_Velocity = velocity;
	}	
}