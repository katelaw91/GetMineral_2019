#version 330 core

layout (location = 0) in vec3 pos;

out vec3 TexCoord;

uniform mat4 pvm;
uniform mat4 model;

void main()
{
    gl_Position = pvm * model * vec4(pos, 1.0);
	TexCoord = pos;
};
