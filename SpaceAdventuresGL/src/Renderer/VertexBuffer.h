#pragma once

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(float* vertices, unsigned int size);		
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetID() const { return m_VertexBufferID; }

private:
	unsigned int m_VertexBufferID;
};