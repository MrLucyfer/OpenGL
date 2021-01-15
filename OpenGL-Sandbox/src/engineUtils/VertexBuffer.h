#pragma once
#include "GLCore.h";

class VertexBuffer {
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int getCount() const { return m_Count; }
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};