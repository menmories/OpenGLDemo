#pragma once


#include "glad/khrplatform.h"
#include "glad/glad.h"
#include <string>

class COpenGLTexture
{
public:
	COpenGLTexture();
	~COpenGLTexture();

	inline GLuint GetTextureId()const
	{
		return m_textureId;
	}

private:
	GLuint m_textureId;
};

