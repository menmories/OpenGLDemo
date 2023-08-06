#define _CRT_SECURE_NO_WARNINGS
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

std::string COpenGLShader::LoadFromFile(const std::string& filename)
{
	std::string content;
	FILE* pFile = fopen(filename.c_str(), "r");
	if (!pFile)
	{
		return content;
	}
	const int MAX_BUFFER_SIZE = 1024;
	char buffer[MAX_BUFFER_SIZE] = { 0 };
	while (fgets(buffer, MAX_BUFFER_SIZE - 1, pFile))
	{
		content += buffer;
	}
	fclose(pFile);
	return content;
}
