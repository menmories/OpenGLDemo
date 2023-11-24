/*
* learn opengl tutorial document.
* 英文版：https://learnopengl.com
* 中文版：https://learnopengl-cn.github.io/
* 代码仓库：https://github.com/JoeyDeVries/LearnOpenGL
*/
#include "stb_image.h"
#include <sdl2/SDL.h>
#include "glad/khrplatform.h"
#include "glad/glad.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Shader.h"


#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "glm/gtc/matrix_transform.hpp"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
//#pragma comment(lib, "SDL2-static.lib")
#pragma comment(lib, "SDL2test.lib")

int screen_width = 1200;
int screen_height = 760;
SDL_Window* window = nullptr;
SDL_GLContext context = nullptr;

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
		return 0;
	}
	context = SDL_GL_CreateContext(window);
	if (!InitOgl())
	{
		fprintf(stderr, "Init opengl failed!\n");
		return 0;
	}
	//MessageLoop();
	 // build and compile our shader zprogram
	// ------------------------------------
	Shader ourShader("vertex.glsl", "fragment.glsl");
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// load and create a texture 
	// -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	std::string strImage = "104936448_master1200.jpg";
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(strImage.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

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
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// bind Texture
		glBindTexture(GL_TEXTURE_2D, texture);

		// render container
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/*glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();*/


		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
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
	
	//glOrtho(-1, 1200, 760, -1, 0, 0);
	//glm::ortho(0.0f, (float)screen_width, 0.0f, (float)screen_height, 0.1f, 100.0f);
	
	//glm::vec2 begin, end;
	
	//glm::vec2 pos = glm::lerp(begin, end, 0.5f);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	return true;
}

void OnResize(int width, int height)
{
	screen_width = width;
	screen_height = height;
	glViewport(0, 0, width, height);
	//glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
}

/*void MessageLoop()
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
}*/

