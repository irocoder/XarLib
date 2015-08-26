#include "SpriteBatch.hpp"
#include <iostream>
#include <SDL.h>
#include <chrono>

XL::SpriteBatch::SpriteBatch(int size)
{
	glGenVertexArrays(numBuffers, vaos);
	glGenBuffers(numBuffers, vbos);
	glGenBuffers(numBuffers, ebos);
	
	for (int i = 0; i < numBuffers; i++)
	{
		glBindVertexArray(vaos[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[i]);

		glBufferData(GL_ARRAY_BUFFER, 8 * 4 * size * sizeof(float), NULL, GL_STREAM_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * size * sizeof(unsigned int), NULL, GL_STREAM_DRAW);

		unsigned int* indices = (unsigned int*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

		for (int i = 0; i < size; i++)
		{
			indices[i * 6 + 0] = i * 4;
			indices[i * 6 + 1] = i * 4 + 1;
			indices[i * 6 + 2] = i * 4 + 2;
			indices[i * 6 + 3] = i * 4 + 2;
			indices[i * 6 + 4] = i * 4 + 3;
			indices[i * 6 + 5] = i * 4;
		}

		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

		setupAttribPointers();
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindVertexArray(NULL);
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	}

	glBindVertexArray(vaos[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[0]);
	this->size = size;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

XL::SpriteBatch::~SpriteBatch()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);
}

void XL::SpriteBatch::setupAttribPointers()
{
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

void XL::SpriteBatch::addVertex(float x, float y, float r, float g, float b, float a, float u, float v)
{
	data[vertexCount * 8] = x;
	data[vertexCount * 8 + 1] = y;

	data[vertexCount * 8 + 2] = r;
	data[vertexCount * 8 + 3] = g;
	data[vertexCount * 8 + 4] = b;
	data[vertexCount * 8 + 5] = a;

	data[vertexCount * 8 + 6] = u;
	data[vertexCount * 8 + 7] = v;

	++vertexCount;
}

void XL::SpriteBatch::checkTextureChange(Texture2D* texture)
{
	if(texture->getID() == NULL)
	{
		std::cout << "Null texture in SpriteBatch." << std::endl;
	}

	if(currentTextureID != texture->getID() && currentTextureID != NULL)
	{
		render();
	}

	if(currentTextureID != texture->getID())
	{
		texture->bind();
		currentTextureID = texture->getID();
	}
}

void XL::SpriteBatch::cycleBuffers()
{
	currentBufferIndex++;

	if (currentBufferIndex >= numBuffers)
	{
		currentBufferIndex = 0;
	}

	glBindVertexArray(vaos[currentBufferIndex]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[currentBufferIndex]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[currentBufferIndex]);
}

void XL::SpriteBatch::draw(float x, float y, float width, float height, float originX, float originY, float r, float g, float b, float a)
{
	addVertex(x - originX, y - originY, r, g, b, a); //TOP LEFT
	addVertex(x - originX, y + height - originY, r, g, b, a); //BOTTOM LEFT
	addVertex(x + width - originX, y + height - originY, r, g, b, a); //BOTTOM RIGHT
	addVertex(x + width - originX, y - originY, r, g, b, a); //TOP RIGHT
}

void XL::SpriteBatch::drawLine(float x1, float y1, float x2, float y2, int thickness, unsigned int color, unsigned char alpha)
{
	unsigned char r = color >> 16 & 0x000000ff;
	unsigned char g = color >> 8 & 0x000000ff;
	unsigned char b = color & 0x000000ff;
	float a = (float)alpha / 256.f;

	addVertex(x1, y1, r, g, b, a);
	addVertex(x1, y1 + thickness, r, g, b, a);
	addVertex(x2, y2 + thickness, r, g, b, a);
	addVertex(x2, y2, r, g, b, a);
}


void XL::SpriteBatch::draw(Texture2D* texture, float x, float y, float originX, float originY, float r, float g, float b, float a)
{
	checkTextureChange(texture);

	addVertex(x - originX, y - originY, r, g, b, a, 0, 0); //TOP LEFT
	addVertex(x - originX, y + texture->getHeight() - originY, r, g, b, a, 0, 1); //BOTTOM LEFT
	addVertex(x + texture->getWidth() - originX, y + texture->getHeight() - originY, r, g, b, a, 1, 1); //BOTTOM RIGHT
	addVertex(x + texture->getWidth() - originX, y - originY, r, g, b, a, 1, 0); //TOP RIGHT
}

void XL::SpriteBatch::draw(XL::Texture2D* texture, const Rectangle* rect, float x, float y, float rotation, float originX, float originY, float r, float g, float b, float a)
{
	checkTextureChange(texture);

	float u1 = (float)rect->x / (float)texture->getWidth();
	float v1 = (float)rect->y / (float)texture->getHeight();
	float u2 = (float)(rect->x + rect->width) / (float)texture->getWidth();
	float v2 = (float)(rect->y + rect->height) / (float)texture->getHeight();

	float scaleX = 1;
	float scaleY = 1;

	float cx = originX * scaleX;
	float cy = originY * scaleY;

	if(rotation == 0)
	{
		addVertex(x - originX, y - originY, r, g, b, a, u1, v1); //TOP LEFT
		addVertex(x - originX, y + rect->height - originY, r, g, b, a, u1, v2); //BOTTOM LEFT
		addVertex(x + rect->width - originX, y + rect->height - originY, r, g, b, a, u2, v2); //BOTTOM RIGHT
		addVertex(x + rect->width - originX, y - originY, r, g, b, a, u2, v1); //TOP RIGHT
	}
	else
	{
		float x1, y1, x2, y2, x3, y3, x4, y4;
		
		float p1x = -cx;
		float p1y = -cy;
		float p3x = -cx + rect->width;
		float p3y = -cy + rect->height;

		float cos = std::cos(-rotation);
		float sin = std::sin(-rotation);

		x1 = (cos * p1x - sin * p1y) + x; //TOP LEFT
		y1 = (sin * p1x + cos * p1y) + y;
		x2 = (cos * p1x - sin * p3y) + x; //BOTTOM LEFT
		y2 = (sin * p1x + cos * p3y) + y;
		x3 = (cos * p3x - sin * p3y) + x; //BOTTOM RIGHT
		y3 = (sin * p3x + cos * p3y) + y;
		x4 = (cos * p3x - sin * p1y) + x; //TOP RIGHT
		y4 = (sin * p3x + cos * p1y) + y;

		addVertex(x1, y1, r, g, b, a, u1, v1);
		addVertex(x2, y2, r, g, b, a, u1, v2);
		addVertex(x3, y3, r, g, b, a, u2, v2);
		addVertex(x4, y4, r, g, b, a, u2, v1);
	}
}

void XL::SpriteBatch::drawString(XL::Font* font, const std::string& string, float x, float y, float sx, float sy, float r, float g, float b, float a)
{
	//FONT SCREWING UP EVERYTHING

	checkTextureChange(font);

	float w;
	float h;
	float u1;
	float u2;
	float v1;
	float v2;
	float offsetX = 0;

	XL::Glyph glyph;

	for(int i = 0; i < string.size(); i++)
	{
		glyph = font->glyphs.at(string[i]);
		w = glyph.width * sx;
		h = glyph.height * sy;

		u1 = (float)glyph.x / (float)font->width;
		v1 = (float)glyph.y / (float)font->height;
		u2 = (float)(glyph.x + glyph.width) / (float)font->width;
		v2 = (float)(glyph.y + glyph.height) / (float)font->height; 

		addVertex(x + glyph.bearingX + offsetX, y - glyph.offsetY, r, g, b, a, u1, v1); //TOP LEFT
		addVertex(x + glyph.bearingX + offsetX, y + h - glyph.offsetY, r, g, b, a, u1, v2); // BOTTOM LEFT
		addVertex(x + w + glyph.bearingX + offsetX, y + h - glyph.offsetY, r, g, b, a, u2, v2); //BOTTOM RIGHT
		addVertex(x + w + glyph.bearingX + offsetX, y - glyph.offsetY, r, g, b, a, u2, v1); //TOP RIGHT

		offsetX += glyph.advanceX;
	}
}

void XL::SpriteBatch::render()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);	

	glDrawElements(GL_TRIANGLES, vertexCount / 4 * 6, GL_UNSIGNED_INT, 0);

	//create GLSync object, will let the GPU know when glDrawElements is done

	/*GLsync fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

	if(glClientWaitSync(fence, GL_SYNC_FLUSH_COMMANDS_BIT, 10000000) == GL_TIMEOUT_EXPIRED)
	{
		std::cout << "A: " << fence << "\n";
	}

	glDeleteSync(fence);*/

	cycleBuffers();

	//glDeleteSync(fences[currentBufferIndex]);
	//see if the current buffer is done being used

	data = (float*)glMapBufferRange(GL_ARRAY_BUFFER, 0, size * 4 * 8 * sizeof(float),
		GL_MAP_WRITE_BIT);

	vertexCount = 0;
	currentTextureID = NULL;
}


void XL::SpriteBatch::begin()
{
	glClear(GL_COLOR_BUFFER_BIT);

	data = (float*)glMapBufferRange(GL_ARRAY_BUFFER, 0, size * 4 * 8 * sizeof(float),
		GL_MAP_WRITE_BIT);
}

void XL::SpriteBatch::end()
{
	if(vertexCount > 0)
		render();

	glUnmapBuffer(GL_ARRAY_BUFFER);
}