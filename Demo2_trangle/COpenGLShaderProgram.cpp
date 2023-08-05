#include "COpenGLShaderProgram.h"

COpenGLShaderProgram::COpenGLShaderProgram()
{
	m_shaderProgram = glCreateProgram();
}

COpenGLShaderProgram::~COpenGLShaderProgram()
{
	glDeleteProgram(m_shaderProgram);
}

void COpenGLShaderProgram::AttatchShader(GLuint shader)
{
	glAttachShader(m_shaderProgram, shader);
}

void COpenGLShaderProgram::LinkProgram()
{
	glLinkProgram(m_shaderProgram);
}

void COpenGLShaderProgram::GetProgramiv(GLenum pname, GLint* params)
{
	glGetProgramiv(m_shaderProgram, pname, params);
}

void COpenGLShaderProgram::GetProgramInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	glGetProgramInfoLog(m_shaderProgram, bufSize, length, infoLog);
}

