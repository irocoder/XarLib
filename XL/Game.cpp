#include "Game.hpp"
#include "FileIO.hpp"
#include "Texture2D.hpp"
#include "Timer.hpp"
#include "../opengl/glm/gtc/matrix_transform.hpp"

#include <sstream>
#include <thread>

XL::Game::Game(const std::string& title, int width, int height)
{
	progStart = SDL_GetPerformanceCounter();
	pFreq = SDL_GetPerformanceFrequency() / 1000;

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
	
	context = SDL_GL_CreateContext(window);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetSwapInterval(0);

	if(ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		std::cout << "OpenGL failed to load." << std::endl;
		SDL_GL_DeleteContext(context);
		SDL_Quit();
	}

	SDL_GetWindowSize(window, &this->width, &this->height);

	std::cout << "WIDTH: " << this->width;
	std::cout << " HEIGHT: " << this->height;

	currentShaderProgram = new XL::ShaderProgram("source/shader/default_vertex.glsl", "source/shader/default_fragment.glsl");
}

Uint64 XL::Game::getTicks()
{
	return (SDL_GetPerformanceCounter() - progStart) / pFreq;
}

void XL::Game::swapWindow()
{
	SDL_GL_SwapWindow(window);
}

void XL::Game::start()
{
	while (isRunning)
	{
		if (getTicks() > nextUpdate)
		{
			Begin = getTicks();
			nextUpdate = Begin + TIME_BETWEEN_TICKS;

			checkKeyboard();

			if(isRunning)
			{
				update();
				draw();

				SDL_GL_SwapWindow(window);
			}

			End = getTicks();
		
			if (End - Begin > TIME_BETWEEN_TICKS)
			{
				fps = 1 / (End - Begin);
			}
			else
			{
				fps = 1000 / TIME_BETWEEN_TICKS;
			}

			//std::cout << "DURATION: " << End - Begin << '\n';
		}
	
	}
}


XL::Game::~Game()
{
	std::cout << "DELETING CONTEXT!" << std::endl;
	delete currentShaderProgram;
	SDL_GL_DeleteContext(context);
	//SDL_Quit();
}

XL::ShaderProgram* XL::Game::getShaderProgram() const
{
	return currentShaderProgram;
}

void XL::Game::quit()
{
	std::cout << "I QUIT NO 2" << std::endl;
	isRunning = false;
}

void XL::Game::setShaderProgram(XL::ShaderProgram* program)
{
	delete currentShaderProgram;

	currentShaderProgram = program;
	currentShaderProgram->bind();
}
