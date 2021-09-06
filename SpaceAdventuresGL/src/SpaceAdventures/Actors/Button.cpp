#include "sapch.h"
#include "Button.h"
#include "Novaura/Input/InputHandler.h"
#include <spdlog/spdlog.h>

namespace SpaceAdventures {

	Button::Button(std::string_view fileName, ButtonType type, const glm::vec2& position, const glm::vec2& scale)
		: m_ButtonType(type)
	{
		//m_Rect = std::make_unique<Novaura::Rectangle>();
		m_Rect = std::make_unique<Novaura::Rectangle>(position, scale);
		m_TextureFile = fileName;
	}

	void Button::Update()
	{
		const bool state = Novaura::InputHandler::IsRectHovered(GetRectangle());
		if (state && !m_IsHovered)
		{			
			m_Rect->m_Color = glm::vec4(1.25f, 1.25f, 1.25f, 1.0f);
			m_IsHovered = true;					
		}		
		else if(!state && m_IsHovered)
		{
			m_Rect->m_Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);			
			m_IsHovered = false;			
		}
	}

}