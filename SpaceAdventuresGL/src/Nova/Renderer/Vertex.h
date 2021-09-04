#pragma once

#include <glm/glm.hpp>

struct VertexData
{
	VertexData(const::glm::vec3& position, const glm::vec4& color) : Position(position), Color(color) {}
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
};