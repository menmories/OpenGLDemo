#include "COpenGLShader.h"

COpenGLShader::COpenGLShader(GLuint shaderType)
{
	m_shader = glCreateShader(shaderType);
}

COpenGLShader::~COpenGLShader()
{
	glDeleteShader(m_shader);
}

void COpenGLShader::ShaderSource(GLsizei count, const GLchar* const* string, const GLint* length)
{
	glShaderSource(m_shader, count, string, length);
}

void COpenGLShader::CompileShader()
{
	glCompileShader(m_shader);
}

void COpenGLShader::GetShaderiv(GLenum pname, GLint* params)
{
	glGetShaderiv(m_shader, pname, params);
}

void COpenGLShader::GetShaderInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	glGetShaderInfoLog(m_shader, bufSize, length, infoLog);
}
