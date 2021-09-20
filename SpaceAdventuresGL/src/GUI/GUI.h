#pragma once
#include "Button.h"
#include "TextToggleButton.h"

namespace GUI {

	class Interface
	{
	public:
		static void AddToggleButton(const std::string& text, const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& fillColor, const glm::vec4& outlineColor, Novaura::Command command);
		static void ClearButtons();
		static void Update();
		static void Draw();

	private:
		static std::vector<std::unique_ptr<Button>> s_ButtonList;

	};
}