/*
* learn opengl tutorial document.
* 英文版：https://learnopengl.com
* 中文版：https://learnopengl-cn.github.io/
* 代码仓库：https://github.com/JoeyDeVries/LearnOpenGL
*/

#include <sdl2/SDL.h>
#include "glad/khrplatform.h"
#include "glad/glad.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "OpenGLFragmentShader.h"
#include "OpenGLVertexShader.h"
#include "COpenGLShaderProgram.h"
#include "COpenGLTexture.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "glm/gtc/matrix_transform.hpp"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
//#pragma comment(lib, "SDL2-static.lib")
#pragma comment(lib, "SDL2test.lib")

class Render
{
public:
	Render()
	{
		//EBO使用
		//GLfloat vertices[] = {
		//	0.5f, 0.5f, 0.0f,   // 右上角
		//	0.5f, -0.5f, 0.0f,	// 右下角
		//	-0.5f, -0.5f, 0.0f, // 左下角
		//	-0.5f, 0.5f, 0.0f   // 左上角
		//};

		float vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};

		GLuint indices[] = { // 注意索引从0开始! 
			0, 1, 3, // 第一个三角形
			1, 2, 3  // 第二个三角形
		};


		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);


		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string strImage = "D:\\GitHub\\OpenGLDemo\\Output\\x64\\4234d5e279ff64c948af90bba5e2f203.jpg";
		if (!m_texture.LoadTexture(strImage))
		{
			printf("LoadTexture failed!\n");
			return;
		}

		//设置顶点数据输入
		//glGenBuffers(1, &VBO);
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		/* 
		* 功能：专门用来把用户定义的数据复制到当前绑定缓冲的函数。它的第一个参数是目标缓冲的类型：
		* 顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上。第二个参数指定传输数据的大小(以字节为单位)；
		* 用一个简单的sizeof计算出顶点数据大小就行。第三个参数是我们希望发送的实际数据。
		* glBufferData
		* 参数四：data
		* GL_STATIC_DRAW ：数据不会或几乎不会改变。
		* GL_DYNAMIC_DRAW：数据会被改变很多。
		* GL_STREAM_DRAW ：数据每次绘制时都会改变。
		*/
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//申请一个shader
		//const char* vertexShaderSource = DEFAULT_VERTEXT_SHADER_STRING;

		std::string shaderStr = COpenGLShader::LoadFromFile("vertex.glsl");
		const char* vertexShaderSource = shaderStr.c_str();
		m_vertexShader.ShaderSource(1, (const char* const*) &vertexShaderSource, nullptr);
		m_vertexShader.CompileShader();
		GLint bSuccess = false;
		m_vertexShader.GetShaderiv(GL_COMPILE_STATUS, &bSuccess);
		if (!bSuccess)
		{
			printf("vertex shader compile failed!\n");
			return;
		}

		shaderStr = COpenGLShader::LoadFromFile("fragment.glsl");
		const char* fragmentShaderSouce = shaderStr.c_str();
		m_fragShader.ShaderSource(1, &fragmentShaderSouce, nullptr);
		m_fragShader.CompileShader();
		m_fragShader.GetShaderiv(GL_COMPILE_STATUS, &bSuccess);
		if (!bSuccess)
		{
			printf("fragment shader compile failed!\n");
			return;
		}

		m_shaderProgram.AttatchShader(m_vertexShader.GetShaderId());
		m_shaderProgram.AttatchShader(m_fragShader.GetShaderId());
		m_shaderProgram.LinkProgram();
		m_shaderProgram.GetProgramiv(GL_LINK_STATUS, &bSuccess);
		if (!bSuccess)
		{
			printf("Program link failed!\n");
			return;
		}
		/*
		* 第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
		* 第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
		* 第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
		* 下个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
		* 第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个GLfloat之后，我们把步长设置为3 * sizeof(GLfloat)。要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子(译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节)。
		* 最后一个参数的类型是GLvoid*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。
		*/
		//位置属性
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//颜色属性
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//贴图属性
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		

		//设置为线框模式
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//设置为默认模式
	}

	void OnRender()
	{
		//glBindVertexArray(VAO);
		/*glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);*/
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glUseProgram(m_shaderProgram.GetShaderProgramId());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture.GetTextureId());

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	COpenGLVertexShader m_vertexShader;
	COpenGLFragmentShader m_fragShader;
	COpenGLShaderProgram m_shaderProgram;
	COpenGLTexture m_texture;
};
int screen_width = 1200;
int screen_height = 760;
SDL_Window* window = nullptr;
SDL_GLContext context = nullptr;
Render* g_render = nullptr;
bool InitOgl();
void OnRender();
void OnResize(int width, int height);
void MessageLoop();
//开启控制台UTF-8编码
void EnableUtf8CodePage()
{
	FILE* pFile = _popen("chcp 65001", "r");
	if (!pFile)
	{
		return;
	}
	_pclose(pFile);
}
int main(int argc, char** argv)
{
	EnableUtf8CodePage();
	int res = SDL_Init(SDL_INIT_VIDEO);
	if (res != 0)
	{
		fprintf(stderr, "SDL_Init error, error code:%d\n", res);
		return -1;
	}
	
	window = SDL_CreateWindow("Simple2D", 130, 100, screen_width, screen_height, 
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		fprintf(stderr, "SDL_CreateWindow failed!\n");
		goto App_Quit;
	}
	context = SDL_GL_CreateContext(window);
	if (!InitOgl())
	{
		fprintf(stderr, "Init opengl failed!\n");
		goto App_Quit;
	}
	MessageLoop();
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
App_Quit:
	SDL_Quit();
	return 0;
}

bool InitOgl()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	int res = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
	if (!res)
	{
		return false;
	}
	g_render = new Render();
	//glOrtho(-1, 1200, 760, -1, 0, 0);
	glm::ortho(0.0f, (float)screen_width, 0.0f, (float)screen_height, 0.1f, 100.0f);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	return true;
}

void OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	g_render->OnRender();
	SDL_GL_SwapWindow(window);
}

void OnResize(int width, int height)
{
	screen_width = width;
	screen_height = height;
	glViewport(0, 0, width, height);
}

void MessageLoop()
{
	SDL_Event sdlEvent;
	bool bQuit = false;
	while (!bQuit)
	{
		if (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
			{
				bQuit = true;
				break;
			}
			case SDL_WINDOWEVENT:
			{
				//窗口大小改变事件
				if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					printf("window resizeD\n");
					OnResize(sdlEvent.window.data1, sdlEvent.window.data2);
				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				break;
			}
			case SDL_KEYDOWN:
			{
				break;
			}
			case SDL_KEYUP:
			{
				break;
			}
			default:
				break;
			}
		}
		OnRender();
	}
}

