#version 330 core

layout (location = 0) in vec3 pos;

out vec3 TexCoord;

uniform mat4 pvm;
uniform mat4 model;

void main()
{
	vec4 apos = pvm * model * vec4(pos, 1.0);
    gl_Position = apos.xyww;
	TexCoord = pos;
};
