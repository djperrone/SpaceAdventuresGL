#include "sapch.h"
#include "TextToggleButton.h"
#include "Novaura/Input/InputHandler.h"
namespace GUI {


	TextToggleButton::TextToggleButton(const std::string& text, const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& fillColor, const glm::vec4& outlineColor, Novaura::Command command)
	{
		m_Text = text;
		m_Rect = std::make_unique<Novaura::Rectangle>(pos, scale, fillColor);
		m_DefaultColor = fillColor;
		m_OutlineColor = outlineColor;
		m_Command = std::move(command);
	}

	void TextToggleButton::Update()
	{
		const bool state = Novaura::InputHandler::IsRectHovered(*m_Rect);
		if (state && !m_IsHovered)
		{
			m_Rect->SetColor(m_DefaultColor + 0.25f);
			m_IsHovered = true;
		}
		else if (!state && m_IsHovered)
		{
			m_Rect->SetColor(m_DefaultColor);
			m_IsHovered = false;
		}
	}

	void TextToggleButton::Execute()
	{
		m_Command.Execute();
	}


}