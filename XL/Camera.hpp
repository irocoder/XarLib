#ifndef XL_CAMERA_HPP
#define XL_CAMERA_HPP

#include "Game.hpp"
#include "../opengl/glm/glm.hpp"

namespace XL
{
class Camera
{
	public:
		Camera(XL::Game* game, int width, int height);
		~Camera();

		void translate(float x, float y);

		void setPosition(float x, float y);
		void setRotation(float rotation);
		void setupProjection(int width, int height);
		void setZoom(float zoom);

		void update();

		glm::vec2 getOffset();

	private:
		XL::ShaderProgram* shaderProgram;
		glm::mat4 rotationMatrix;
		glm::mat4 projectionMatrix;
		glm::vec2 offset;

		GLuint rotationMatrixID;
		GLuint projectionMatrixID;
		GLuint offsetID;

		float scaleX = 0;
		float scaleY = 0;
		int width, height; //viewport width and height
};
};

#endif