#ifndef XL_GAME_HPP
#define XL_GAME_HPP

#include "SpriteBatch.hpp"
#include "ShaderProgram.hpp"
#include <iostream>
#include <SDL.h>
#include <sstream>
#include <chrono>
#include <string>

//#include "../opengl/gl_core_3_3.h"
//#include "../opengl/glm/glm.hpp"

namespace XL
{
class Game
{
	public:
		Game(const std::string& title, int width, int height);
		~Game();

		void setShaderProgram(XL::ShaderProgram* program);
		XL::ShaderProgram* getShaderProgram() const;

		virtual void update() {};
		virtual void draw() {};
		void start();
		void quit();
		void swapWindow();

		SDL_Window* window; //public for debugging, make private

	protected:
		int width;
		int height;
		Uint32 fps;

		int loops = 0;

	private:
		SDL_GLContext context;

		XL::ShaderProgram* currentShaderProgram;

		float camX;
		float camY;

		virtual void checkKeyboard() {};
		void calculateFPS();

		bool isRunning = true;

		Uint64 progStart;
		Uint64 Begin = 0, End = 0, nextUpdate = 0;
		Uint64 pFreq;

		const Uint32 TICKS_PER_SECOND = 50;
		const Uint32 TIME_BETWEEN_TICKS = 1000 / TICKS_PER_SECOND;
		int drawn = 0;

		Uint64 getTicks();

	protected:
};
};

#endif