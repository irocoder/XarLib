#ifndef XL_SPRITEBATCH_HPP
#define XL_SPRITEBATCH_HPP

#include "Texture2D.hpp"
#include "Rectangle.hpp"
#include "Font.hpp"

#include "../opengl/gl_core_3_3.h"
#include "../opengl/glm/glm.hpp"
#include "../opengl/glm/gtc/matrix_transform.hpp"

#include <vector>

namespace XL
{
class SpriteBatch
{
	public:
		//size of the spritebatch in quads
		SpriteBatch(int size);
		~SpriteBatch();

		void addVertex(float x, float y, float r, float g, float b, float a = 1, float u = 0, float v = 0);
		void draw(float x, float y, float width, float height, float originX, float originY, float r, float g, float b, float a);
		void draw(XL::Texture2D* texture, float x, float y, float originX = 0, float originY = 0, float r = 1, float g = 1, float b = 1, float a = 1);
		void draw(XL::Texture2D* texture, const Rectangle* rect, float x, float y, float rotation, float originX = 0, float originY = 0, float r = 1, float g = 1, float b = 1, float a = 1);
		void drawString(XL::Font* font, const std::string& string, float x, float y, float sx, float sy, float r = 1, float g = 1, float b = 1, float a = 1);
		void drawLine(float x1, float y1, float x2, float y2, int thickness, unsigned int color, unsigned char alpha);

		void begin();
		void render();
		void end();

		void checkTextureChange(Texture2D* texture);

	private:
		const static int numBuffers = 3;

		GLuint currentVao;
		GLuint currentVbo;

		GLuint vaos[numBuffers];
		GLuint vbos[numBuffers];
		GLuint ebos[numBuffers];
		//GLsync fences[numBuffers];
		void cycleBuffers();
		int currentBufferIndex = 0;
		GLuint currentTextureID = 0;

		float* data = NULL; //don't delete this

		int vertexCount = 0;
		int size; //size of the spritebatch in quads

		void setupAttribPointers();
};
};

#endif