#pragma once

/* 
* Ƭ����ɫ������ҪĿ���Ǽ���һ�����ص�������ɫ��
* ��Ҳ������OpenGL�߼�Ч�������ĵط���ͨ����
* Ƭ����ɫ������3D���������ݣ�������ա���Ӱ��
* �����ɫ�ȵȣ�����Щ���ݿ��Ա����������������ص���ɫ��
*/

#include "COpenGLShader.h"

#define DEFAULT_FRAGMENT_SHADER_STRING "#version 330 core\n\
out vec4 color;\n\
void main()\n\
{\n\
	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n\
}\n\
\n"


class COpenGLFragmentShader : public COpenGLShader
{
public:
	COpenGLFragmentShader();
	~COpenGLFragmentShader();
};

