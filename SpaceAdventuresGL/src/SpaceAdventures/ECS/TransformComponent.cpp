#include "sapch.h"
#include "TransformComponent.h"

namespace SpaceAdventures {
	
	TransformComponent::TransformComponent(const glm::vec2& position, const glm::vec2& scale)
		: m_Position(position, 0.0f), m_Scale(scale, 1.0f) {}

}