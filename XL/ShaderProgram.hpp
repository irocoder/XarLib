#ifndef XL_SHADER_PROGRAM_HPP
#define XL_SHADER_PROGRAM_HPP

#include "../opengl/gl_core_3_3.h"

#include <string>

namespace XL
{
class ShaderProgram
{
public:
	ShaderProgram(const std::string& vShaderPath, const std::string& fShaderPath);
	~ShaderProgram();

	void bind();
	void unbind();

	GLuint get() { return program; }

private:
	void loadShaders();

	std::string vertexShaderSource;
	std::string fragmentShaderSource;

	const char* vertexSource;
	const char* fragmentSource;

	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint program;

	GLint positionAttribute;
	GLint colorAttribute;
};
};

#endif