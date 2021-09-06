#pragma once

#include "Novaura/Primitives/Rectangle.h"
namespace SpaceAdventures {

	class Actor
	{
	public:
		virtual void Update() = 0;

		inline const Novaura::Rectangle& GetRectangle() const { return *m_Rect; }
		inline Novaura::Rectangle& GetRectangle() { return *m_Rect; }

		inline std::string_view GetTextureFile() { return m_TextureFile; }
		inline const std::string_view GetTextureFile() const { return m_TextureFile; }

	protected:
		std::unique_ptr<Novaura::Rectangle> m_Rect;
		std::string_view m_TextureFile;
	};
}