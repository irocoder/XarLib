#ifndef XL_BITMAP_HPP
#define XL_BITMAP_HPP

#include <string>

namespace XL
{
	#define BITMAP_FILEHEADER_SIZE 14
	#define BITMAP_INFOHEADER_SIZE 40

class Bitmap
{	
	public:
		Bitmap();
		Bitmap(unsigned char* pixels);
		~Bitmap();

		void load(const std::string& filePath);

	private:
		unsigned int width;
		unsigned int height;
		unsigned char fileHeader[14];
		unsigned char infoHeader[40];
		unsigned char* pixels = NULL;

};
};

#endif