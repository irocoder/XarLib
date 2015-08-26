#include "ShaderProgram.hpp"
#include "FileIO.hpp"
#include <iostream>

XL::ShaderProgram::ShaderProgram(const std::string& vShaderPath, const std::string& fShaderPath)
{
	vertexShaderSource = XL::readTXT(vShaderPath);
	fragmentShaderSource = XL::readTXT(fShaderPath);

	vertexSource = vertexShaderSource.c_str(); //does the memory actually get copied over?  recheck this!
	fragmentSource = fragmentShaderSource.c_str();
	//DOUBLE RECHECK MEMORY ALLOCATION OF FRAG_SOURCE AND VERT_SOURCE

	loadShaders();
	bind();
}

void XL::ShaderProgram::bind()
{
	glUseProgram(program);
}

void XL::ShaderProgram::unbind()
{
	glUseProgram(NULL);
}

void XL::ShaderProgram::loadShaders()
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	//glBindFragDataLocation(program, 0, "outputColor");
	glLinkProgram(program);
}

XL::ShaderProgram::~ShaderProgram()
{
	std::cout << "DELETING SHADER-PROGRAM!" << std::endl;
	glLinkProgram(NULL);
	glUseProgram(NULL);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(program);
}