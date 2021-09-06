#pragma once
#include "Actor.h"
#include <glm/glm.hpp>

namespace SpaceAdventures {

	enum class ButtonType
	{
		None = 0,
		Play,
		PauseMenu,
		MainMenu,
		Exit
	};

	class Button : public Actor
	{
	public:

		Button() = default;
		Button(std::string_view fileName, ButtonType type, const glm::vec2& position, const glm::vec2& scale);	

		virtual void Update() override;
	};
}