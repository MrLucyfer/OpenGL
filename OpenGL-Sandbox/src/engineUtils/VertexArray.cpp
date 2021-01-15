#include "VertexArray.h";

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_RenderID);
	glBindVertexArray(m_RenderID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RenderID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RenderID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(VertexBufferLayout& layout)
{
	// README
	auto elements = layout.GetElements();
	unsigned int offset = 0;

	for (int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (void*)offset);
		
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	
}
