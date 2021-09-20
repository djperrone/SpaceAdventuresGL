#pragma once

#include "Novaura/Primitives/Rectangle.h"
#include "Novaura/Input/Command.h"

namespace GUI {

	class Button
	{
	public:
		Button() = default;
		virtual ~Button() = default;

		virtual void Update() = 0;
		virtual void Execute() = 0;

		inline bool IsHovered() { return m_IsHovered; }
		inline void SetHovered(bool isHovered) { m_IsHovered = isHovered; }

		inline const Novaura::Rectangle& GetRectangle() const { return *m_Rect; }
		inline Novaura::Rectangle& GetRectangle() { return *m_Rect; }

		inline std::string_view GetTextureFile() { return m_TextureFile; }
		inline const std::string_view GetTextureFile() const { return m_TextureFile; }
		inline void SetTextureFile(std::string_view texFile) { m_TextureFile = texFile; }

		inline void SetFillColor(const glm::vec4& color) { m_Rect->SetColor(color); }
		inline void SetOutLineColor(const glm::vec4& color) { m_OutlineColor = color; }
		inline void SetOutlineScale(float scale) { m_OutLineScale = scale; }

		inline const glm::vec4& GetOutlineColor() const { return m_OutlineColor; }
		inline const std::string& GetText() const { return m_Text; }

		inline const glm::vec4& GetTextColor() const { return m_TextColor; }
		inline void SetOutlineColor(const glm::vec4& outlineColor) { m_OutlineColor = outlineColor; }


	protected:
		std::string_view m_TextureFile;
		bool m_IsHovered = false;
		std::unique_ptr<Novaura::Rectangle> m_Rect;
		Novaura::Command m_Command;

		std::string m_Text;
		glm::vec4 m_DefaultColor{ 0.0f,0.0f,0.0f,1.0f };
		glm::vec4 m_OutlineColor;
		glm::vec4 m_TextColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		float m_OutLineScale = 1.1f;
	};
}