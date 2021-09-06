#pragma once
#include "Component.h"
#include <glm/glm.hpp>

#include <string_view>

namespace SpaceAdventures {

	class TextureComponent
	{
	public:
		TextureComponent(std::string_view fileName);
		TextureComponent(std::string_view fileName, glm::vec4 color);

		inline glm::vec4& GetColor() { return m_Color; }
		inline const glm::vec4& GetColor()    const { return m_Color; }
		inline void SetColor(const glm::vec4& color) { m_Color = color; }

		inline std::string_view GetTextureFile() { return m_TextureFile; }
		inline const std::string_view GetTextureFile() const { return m_TextureFile; }
		void SetTextureFile(std::string_view textureFile) { m_TextureFile = textureFile; }

	private:
		glm::vec4 m_Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);;
		std::string_view m_TextureFile;

	};
}