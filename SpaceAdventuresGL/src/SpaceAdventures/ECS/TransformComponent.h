#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace SpaceAdventures {

	class TransformComponent
	{

	public:
		TransformComponent() = default;	
		TransformComponent(const glm::vec2 & position, const glm::vec2 & scale);
		~TransformComponent() = default;

	public:
		inline glm::vec3& GetPosition() { return m_Position; }
		inline glm::vec3& GetScale() { return m_Scale; }
		inline float GetRotation() { return m_Rotation; }

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec3& GetScale()    const { return m_Scale; }
		inline const float GetRotation()     const { return m_Rotation; }


		inline void SetPosition(const glm::vec3 & position) { m_Position = position; }
		inline void SetScale(const glm::vec3 & scale) { m_Scale = scale; }
		inline void SetRotation(float rotation) { m_Rotation = rotation; }

	private:
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		float m_Rotation = 0.0f;
	};

}