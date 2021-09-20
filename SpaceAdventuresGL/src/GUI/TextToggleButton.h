#pragma once
#include "GUI/Button.h"

namespace GUI {

	class TextToggleButton : public Button
	{
	public:
		TextToggleButton() = default;
		TextToggleButton(const std::string& text, const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& fillColor, const glm::vec4& outlineColor, Novaura::Command command);
	////	ToggleButton(const std::string& text, const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& fillColor, const glm::vec4& outlineColor, Novaura::Command command);

		virtual void Update() override;
		virtual void Execute() override;



	//	//ToggleButton() = delete;
	//	//ToggleButton(const ToggleButton&) = delete;

	//private:


	};
}