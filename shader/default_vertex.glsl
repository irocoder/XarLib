#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 inputColor;
layout(location = 2) in vec2 texCoords;

uniform mat4 projection;
uniform vec2 offset;

out vec4 vShaderColorOutput;
out vec2 vShaderTexCoordOutput;

void main()
{
	vec2 cameraPos = position - offset;

	gl_Position = projection * vec4(cameraPos, 0.0, 1.0);

	vShaderColorOutput = inputColor;
	vShaderTexCoordOutput = texCoords;
}