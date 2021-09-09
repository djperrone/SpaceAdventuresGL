#pragma once

#include <glm/glm.hpp>

struct VertexData
{
	VertexData(const::glm::vec3& position, const glm::vec4& color, const glm::vec2& texCoord) : Position(position), Color(color), TexCoord(texCoord) {}
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
};

