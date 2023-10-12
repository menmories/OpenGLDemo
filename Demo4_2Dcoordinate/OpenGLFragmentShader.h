#pragma once

/* 
* 片段着色器的主要目的是计算一个像素的最终颜色，
* 这也是所有OpenGL高级效果产生的地方。通常，
* 片段着色器包含3D场景的数据（比如光照、阴影、
* 光的颜色等等），这些数据可以被用来计算最终像素的颜色。
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

