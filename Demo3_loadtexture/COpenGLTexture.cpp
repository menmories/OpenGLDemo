#include "COpenGLTexture.h"
#include "stb_image.h"
COpenGLTexture::COpenGLTexture()
	: m_width(0)
	, m_height(0)
	, m_comp(0)
{
	glGenTextures(1, &m_textureId);
}

COpenGLTexture::~COpenGLTexture()
{
	glDeleteTextures(1, &m_textureId);
}

bool COpenGLTexture::LoadTexture(const std::string& filename)
{
	stbi_uc* data = stbi_load(filename.c_str(), &m_width, &m_height, &m_comp, 4);
	if (!data)
	{
		return false;
	}

	GLenum format = GL_RGB;
	if (m_comp == 1)
	{
		format = GL_RED;
	}
	else if (m_comp == 3)
	{
		format = GL_RGB;
	}
	else if (m_comp == 4)
	{
		format = GL_RGBA;
	}
	else
	{
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, m_textureId);
	//设置texture属性
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNALED, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	return true;
}
