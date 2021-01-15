#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path):
	m_Path(path), m_Width(0), m_Height(0), m_Bpp(0)
{
	//Flipping the image cos opengl 0,0 is bottom left jeje
	
	//Generate an ID
	glGenTextures(1, &m_RendererID);
	//Bind the actual texture
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	//Set some parameter
	// set the texture wrapping parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// //set texture filtering parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


	stbi_set_flip_vertically_on_load(1);

	m_Data = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_Bpp, 4);

	if (m_Data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}


	//glBindTexture(GL_TEXTURE_2D, 0);

	if (m_Data) {
		stbi_image_free(m_Data);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
}
