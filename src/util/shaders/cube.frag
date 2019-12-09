#version 330 core

in vec3 TexCoord;
out vec4 frag_color;

uniform samplerCube myTexture;

void main()
{
    frag_color = texture(myTexture, TexCoord);
};