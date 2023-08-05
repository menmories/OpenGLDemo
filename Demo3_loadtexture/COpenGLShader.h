#pragma once

#include "glad/khrplatform.h"
#include "glad/glad.h"
#include <string>

class COpenGLShader
{
public:
	COpenGLShader(GLuint shaderType);
	~COpenGLShader();

	void ShaderSource(GLsizei count, const GLchar* const* string, const GLint* length);

	void CompileShader();

	void GetShaderiv(GLenum pname, GLint* params);

	inline GLuint GetShaderId()const
	{
		return m_shader;
	}

	void GetShaderInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog);
private:
	GLuint m_shader;
};

