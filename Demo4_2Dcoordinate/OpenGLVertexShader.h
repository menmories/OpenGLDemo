#pragma once

/*
首先，我们以数组的形式传递3个3D坐标作为图形渲染管线的输入，
用来表示一个三角形，这个数组叫做顶点数据(Vertex Data)；
顶点数据是一系列顶点的集合。一个顶点(Vertex)是一个3D坐标的
数据的集合。而顶点数据是用顶点属性(Vertex Attribute)表示的，
它可以包含任何我们想用的数据，但是简单起见，我们还是假定每个顶点
只由一个3D位置(译注1)和一些颜色值组成的吧。



图形渲染管线的第一个部分是顶点着色器(Vertex Shader)，它把一个单独的顶点作为输入。顶点着色器主要的目的是把3D坐标转为另一种3D坐标（后面会解释），同时顶点着色器允许我们对顶点属性进行一些基本处理。

图元装配(Primitive Assembly)阶段将顶点着色器输出的所有顶点作为输入（如果是GL_POINTS，那么就是一个顶点），并所有的点装配成指定图元的形状；本节例子中是一个三角形。

图元装配阶段的输出会传递给几何着色器(Geometry Shader)。几何着色器把图元形式的一系列顶点的集合作为输入，它可以通过产生新顶点构造出新的（或是其它的）图元来生成其他形状。例子中，它生成了另一个三角形。

几何着色器的输出会被传入光栅化阶段(Rasterization Stage)，这里它会把图元映射为最终屏幕上相应的像素，生成供片段着色器(Fragment Shader)使用的片段(Fragment)。在片段着色器运行之前会执行裁切(Clipping)。裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率。
*/

#include "COpenGLShader.h"

#define DEFAULT_VERTEXT_SHADER_STRING "#version 330 core\n\
layout(location = 0) in vec3 position;\n\
void main()\n\
{\n\
gl_Position = vec4(position.x, position.y, position.z, 1.0);\n\
}\n"


	



class COpenGLVertexShader : public COpenGLShader
{
public:
	COpenGLVertexShader();
	~COpenGLVertexShader();

};

