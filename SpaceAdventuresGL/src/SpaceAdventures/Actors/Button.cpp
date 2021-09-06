#include "sapch.h"
#include "Button.h"

namespace SpaceAdventures {

	Button::Button(std::string_view fileName, ButtonType type, const glm::vec2& position, const glm::vec2& scale)
	{
		//m_Rect = std::make_unique<Novaura::Rectangle>();
		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(0.4f, 0.2f, 0.8f, 1.0f));
		m_TextureFile = fileName;
	}

	void Button::Update()
	{
	}

}