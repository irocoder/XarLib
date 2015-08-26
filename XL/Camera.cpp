#include "Camera.hpp"
#include "../opengl/glm/gtc/matrix_transform.hpp"

XL::Camera::Camera(XL::Game* game, int width, int height)
{
	this->shaderProgram = game->getShaderProgram();
	offsetID = glGetUniformLocation(this->shaderProgram->get(), "offset");

	setPosition(0, 0);
	setupProjection(width, height);

	this->width = width;
	this->height = height;
}

XL::Camera::~Camera()
{
	shaderProgram = NULL;
}

void XL::Camera::translate(float x, float y)
{
	offset.x += x;
	offset.y += y;

	glUniform2fv(offsetID, 1, &offset[0]);
}

void XL::Camera::setPosition(float x, float y)
{
	offset.x = x;
	offset.y = y;

	//shaderProgram->bind();
	glUniform2fv(offsetID, 1, &offset[0]);
	//shaderProgram->unbind();
}

void XL::Camera::setRotation(float rotation)
{
	rotationMatrix[0][0] = std::cos(rotation);
	rotationMatrix[1][0] = -std::sin(rotation);
	rotationMatrix[0][1] = std::sin(rotation);
	rotationMatrix[1][1] = std::cos(rotation);

	//shaderProgram->bind();
	//glUniformMatrix4fv(
}

void XL::Camera::setZoom(float zoom)
{
	projectionMatrix = glm::ortho(0.f, (float)width * (1.f/zoom), (float)height * (1.f/zoom), 0.f); //adjust 0.5 for zoom
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
}

glm::vec2 XL::Camera::getOffset()
{
	return offset;
}

void XL::Camera::setupProjection(int width, int height)
{
	glViewport(0, 0, width, height);
	projectionMatrix = glm::ortho(0.f, (float)width * 1.f, (float)height * 1.f, 0.f); //adjust 0.5 for zoom
	projectionMatrixID = glGetUniformLocation(shaderProgram->get(), "projection");

	//shaderProgram->bind();
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);
	//shaderProgram->unbind();
}