#include "COpenGLTexture.h"

COpenGLTexture::COpenGLTexture()
{
	glGenTextures(1, &m_textureId);
}

COpenGLTexture::~COpenGLTexture()
{
	glDeleteTextures(1, &m_textureId);
}
