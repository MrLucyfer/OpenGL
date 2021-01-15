#pragma once
#include "GLCore.h"
#include "VertexBufferLayout.h"


class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(VertexBufferLayout& layout);

private:
	unsigned int m_RenderID;
};