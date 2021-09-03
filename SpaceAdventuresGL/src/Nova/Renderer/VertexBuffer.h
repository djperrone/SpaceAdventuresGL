#pragma once

#include "Nova/Renderer/Vertex.h"

namespace Nova {

	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(float* vertices, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void UnBind() const;
		void SetData(const std::vector<VertexData>& vertices);
		void SetData(float* vertices, unsigned int size);

		inline unsigned int GetID() const { return m_VertexBufferID; }

	private:
		unsigned int m_VertexBufferID;
	};
}