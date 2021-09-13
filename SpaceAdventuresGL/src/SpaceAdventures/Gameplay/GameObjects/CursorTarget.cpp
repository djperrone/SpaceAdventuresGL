#include "sapch.h"
#include "CursorTarget.h"
#include "Novaura/Novaura.h"

namespace SpaceAdventures {

	CursorTarget::CursorTarget()
	{
		m_TextureFile = "Assets/Textures/CursorTarget.png";
		auto [x, y] = Novaura::InputHandler::GetMouseDeviceCoordinates();

		m_Rect = std::make_unique<Novaura::Rectangle>(glm::vec2(static_cast<float>(x), static_cast<float>(y)), glm::vec2(0.10f, 0.10f));
	}

	void CursorTarget::Update(float dt)
	{
		auto[x,y]  = Novaura::InputHandler::GetMouseDeviceCoordinates();
		m_Rect->SetPosition(glm::vec3(static_cast<float>(x),static_cast<float>(y),0.0f));
		
	}

	void CursorTarget::CheckForCollision(const std::vector<std::shared_ptr<Ship>>& shipList)
	{
		for (const auto& ship : shipList)
		{
			if (ship->IsAlive())
			{
				bool state = Novaura::InputHandler::IsRectHovered(ship->GetRectangle());
				if (state && ship->GetTeam() == Team::Enemy)
				{
					m_IsHovered = true;
				}
			}
					
		}

		if (m_IsHovered)
		{
			m_Rect->SetColor(glm::vec4(0.8f, 0.2f, 0.2f, 1.0f));
		}
		else
		{
			m_Rect->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		m_IsHovered = false;
		
	}	

}