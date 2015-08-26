#version 330

uniform sampler2D texture_diffuse;

in vec4 vShaderColorOutput;
in vec2 vShaderTexCoordOutput;

out vec4 outputColor;

void main()
{
	if(vShaderTexCoordOutput.x != 0 && vShaderTexCoordOutput.y != 0)
		outputColor = texture2D(texture_diffuse, vShaderTexCoordOutput) * vShaderColorOutput;
	else
		outputColor = vShaderColorOutput;
}