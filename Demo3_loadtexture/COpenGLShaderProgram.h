#pragma once

#include "glad/khrplatform.h"
#include "glad/glad.h"
#include <string>



class COpenGLShaderProgram
{
public:
	COpenGLShaderProgram();
	~COpenGLShaderProgram();

	void AttatchShader(GLuint shader);

	void LinkProgram();

	void GetProgramiv(GLenum pname, GLint* params);

	void GetProgramInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog);

	inline GLuint GetShaderProgramId()const
	{
		return m_shaderProgram;
	}
private:
	GLuint m_shaderProgram;
};

