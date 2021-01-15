#include "Renderer.h"

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& vao, const VertexBuffer& vbo)
{
	vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, vbo.getCount() / sizeof(float));
}

void Renderer::Draw(const VertexArray& vao, const VertexBuffer& vbo, const IndexBuffer& ibo) const
{
	vao.Bind();
	ibo.Bind();
	glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0);
}


