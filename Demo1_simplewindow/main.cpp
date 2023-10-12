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


#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
//#pragma comment(lib, "SDL2-static.lib")
#pragma comment(lib, "SDL2test.lib")

SDL_Window* window = nullptr;
SDL_GLContext context = nullptr;

bool InitOgl();
void OnRender();
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
	
	window = SDL_CreateWindow("OpenGL窗口", 130, 100, 1200, 760, 
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
	glClearColor(0.2f, 0.8f, 0.92f, 1.0f);
	return true;
}

void OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	SDL_GL_SwapWindow(window);
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

