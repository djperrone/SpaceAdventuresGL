#include "sapch.h"
#include "TextureComponent.h"

namespace SpaceAdventures {

	TextureComponent::TextureComponent(std::string_view fileName)
		: m_TextureFile(fileName) {}

	TextureComponent::TextureComponent(std::string_view fileName, glm::vec4 color)
		: m_TextureFile(fileName), m_Color(color) {}	

}