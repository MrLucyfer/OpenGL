#pragma once
#include <GLCore.h>


class Texture {
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
	std::string m_Path;
	unsigned char* m_Data;
	int m_Width, m_Height, m_Bpp;
};