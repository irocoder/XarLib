#include "Bitmap.hpp"
#include <iostream>
#include <fstream>

XL::Bitmap::Bitmap()
{
}

XL::Bitmap::Bitmap(unsigned char* newPixels)
{
	pixels = newPixels;
}

XL::Bitmap::~Bitmap()
{
	delete pixels;
}

void XL::Bitmap::load(const std::string& filePath)
{
	std::basic_ifstream<unsigned char> file(filePath, std::ios::binary);
	file.read(fileHeader, BITMAP_FILEHEADER_SIZE);

	if(fileHeader[0] == 'B' && fileHeader[1] == 'M')
	{
		std::cout << "FILE IS A BMP" << std::endl;

		file.read(infoHeader, BITMAP_INFOHEADER_SIZE);

		width = (unsigned int)infoHeader[4];
		height = (unsigned int)infoHeader[8];

		std::cout << "BMP WIDTH: " << width << std::endl;
		std::cout << "BMP HEIGHT: " << height << std::endl;

		//if((unsigned int)infoHeader[14] == 8)
		//{
			std::cout << "IS " << (unsigned int)infoHeader[14] << "-BIT" << std::endl;
			pixels = new unsigned char[width * height * 3];
			file.read(pixels, width * height * 3);

			std::cout << (unsigned int)pixels[0] << std::endl;
			std::cout << (unsigned int)pixels[1] << std::endl;
			std::cout << (unsigned int)pixels[2] << std::endl;

			std::cout << (unsigned int)pixels[3] << std::endl;
			std::cout << (unsigned int)pixels[4] << std::endl;
			std::cout << (unsigned int)pixels[5] << std::endl;

			std::cout << (unsigned int)pixels[6] << std::endl;
			std::cout << (unsigned int)pixels[7] << std::endl;
			std::cout << (unsigned int)pixels[8] << std::endl;

			std::cout << (unsigned int)pixels[9] << std::endl;
			std::cout << (unsigned int)pixels[10] << std::endl;
			std::cout << (unsigned int)pixels[11] << std::endl;

			std::cout << (unsigned int)pixels[12] << std::endl;
			std::cout << (unsigned int)pixels[13] << std::endl;
			std::cout << (unsigned int)pixels[14] << std::endl;

			for(unsigned int i = 0; i < width * height * 3; i += 3)
			{
				unsigned char temp = pixels[i];
				pixels[i] = pixels[i + 2];
				pixels[i + 2] = temp;
			}
		//}	
		//else if((unsigned int)infoHeader[14] == 24)
		//{
		//}
	}
	else
	{
		std::cout << "FILE IS NOT A BMP" << std::endl;
	}
}
