#include "Font.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

#include <iostream>
#include <algorithm>
#include <fstream>

#include FT_BITMAP_H

XL::Font::Font()
{
	//add default font


	/*if(FT_Init_FreeType(&freeType))
		std::cout << "Could not initialize FreeType" << std::endl;
	else
		std::cout << "FreeType initialized!" << std::endl;*/
}

XL::Font::Font(const std::string& filePath)
{
	if (FT_Init_FreeType(&freeType))
		std::cout << "Could not initialize FreeType" << std::endl;
	//else
		//std::cout << "FreeType initialized!" << std::endl;

	load(filePath);
}

XL::Font::~Font()
{
	std::cout << "DELETING FONT!----------------------------" << std::endl;

	glDeleteTextures(1, &id); //recheck this
}

void XL::Font::load(const std::string& filePath)
{
	if (FT_New_Face(freeType, filePath.c_str(), 0, &face))
		std::cout << "Could not load " << filePath  << std::endl;

	FT_Set_Pixel_Sizes(face, 0, 20);
	glyph = face->glyph;

	std::vector<unsigned char> newData;
	std::string charset("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 `~!@#$%^&*()-_+=[{}]\"':;|/.,<>?");

	for(int i = 0; i < charset.size(); i++)
	{	
		if (FT_Load_Char(face, charset[i], FT_LOAD_RENDER))
			std::cout << "Could not load char " << '"' << charset[i] << '"' << std::endl;
	
		width += glyph->bitmap.width;
		height = std::max(glyph->bitmap.rows, height);

		newData.resize(width * height, 0);
		
		glyphs.emplace(charset[i], XL::Glyph(width - glyph->bitmap.width, 0, glyph->bitmap.width, 
			glyph->bitmap.rows, glyph->metrics.horiAdvance / 64, glyph->metrics.horiBearingX / 64, 
			glyph->metrics.horiBearingY / 64));

		for(int j = 0; j < height; j++)
		{
			for(int k = width - glyph->bitmap.width; k < width; k++)
			{
				if(j < glyph->bitmap.rows)
				{
					newData.insert(newData.begin() + j * width + k, 
					glyph->bitmap.buffer[(j * width + k) - ((width - glyph->bitmap.width) * (j + 1))]);
				}
				else
				{
					newData.insert(newData.begin() + j * width + k, 0);
				}
			}	

		}
	}

	//stbi_write_bmp("STB_OUT.bmp", width, height, 1, newData.data());

	//convert to RGBA format
	unsigned char* RGBA = new unsigned char [width * height * 4];

	for(int i = 0; i < width * height * 4; i += 4)
	{
		if(newData[i / 4] == 0)
		{
			RGBA[i] = 0;
			RGBA[i + 1] = 0;
			RGBA[i + 2] = 0;
			RGBA[i + 3] = 0;
		}
		else if (newData[i / 4] == 255)
		{
			RGBA[i] = 255;
			RGBA[i + 1] = 255;
			RGBA[i + 2] = 255;
			RGBA[i + 3] = 255;
		}
		else
		{
			RGBA[i] = RGBA[i + 1] = RGBA[i + 2] = newData[i / 4];
			RGBA[i + 3] = newData[i / 4];
		}
	}

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, newData.data());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, RGBA);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, NULL);

	delete[] RGBA;
}
