#pragma once
#include "GLCore.h"
#include "VertexArray.h"
#include "VertexBuffer.h";
#include "IndexBuffer.h";

class Renderer {
public:
	
	void Clear() const;
	void Draw(const VertexArray& vao, const VertexBuffer& vbo);
	void Draw(const VertexArray& vao, const VertexBuffer& vbo, const IndexBuffer& ibo) const;
private:
};