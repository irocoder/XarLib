#ifndef XL_TEXTURE_2D_HPP
#define XL_TEXTURE_2D_HPP

#include "../opengl/gl_core_3_3.h"
#include <fstream>
#include <string>
#include <png.h>

#define PNG_SIG_SIZE 8

namespace XL
{
class Texture2D
{
	public:
		Texture2D();
		Texture2D(const Texture2D& texture);
		Texture2D(const std::string& file);
		~Texture2D();

		void bind();
		void unbind();

		GLuint loadPNG(const std::string& filePNG);
		void deleteTexture();

		GLuint getID() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;

		int offsetX;
		int offsetY;

		XL::Texture2D& XL::Texture2D::operator=(const XL::Texture2D texture);

	private:
		std::string fileName;
		std::ifstream file;

	protected:
		GLuint id;
		unsigned int width;
		unsigned int height;
};

void readData(png_structp pngPtr, png_bytep data, png_size_t length);

};

#endif