#include "FileIO.hpp"

#include <fstream>
#include <exception>
#include <iostream>

std::string XL::readTXT(const std::string& filePath)
{
	std::ifstream input(filePath);

	if(!input)
	{
		std::cout << "Filepath : " << filePath << " not valid" << std::endl;
		//return NULL;
	}

	std::string output;
	std::string s;

	while(std::getline(input, s))
	{
		output.append(s);
		output.append("\n");
	}

	input.close();
	return output;
}