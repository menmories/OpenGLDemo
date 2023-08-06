#pragma once


#include "glad/khrplatform.h"
#include "glad/glad.h"
#include <string>

class COpenGLTexture
{
public:
	COpenGLTexture();
	~COpenGLTexture();

	bool LoadTexture(const std::string& filename);


	inline GLuint GetTextureId()const
	{
		return m_textureId;
	}

private:
	GLuint m_textureId;
	int m_width;
	int m_height;
	int m_comp;
};

