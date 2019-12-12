#include "texture3D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <vector>


Texture3D::Texture3D()
	: mTexture(0) {}

Texture3D::Texture3D(const string& filename)
	: mTexture(0)
{
	texture.push_back(filename);
	texture.push_back(filename);
	texture.push_back(filename);
	texture.push_back(filename);
	texture.push_back(filename);
	texture.push_back(filename);

	loadTexture();
}

Texture3D::Texture3D(const string& side, const string& top)
	: mTexture(0)
{
	texture.push_back(side);
	texture.push_back(side);
	texture.push_back(top);
	texture.push_back(side);
	texture.push_back(side);
	texture.push_back(side);


	loadTexture();
}

Texture3D::Texture3D(const string& side, const string& top, const string &bottom)
	: mTexture(0)
{
	texture.push_back(side);
	texture.push_back(side);
	texture.push_back(top);
	texture.push_back(bottom);
	texture.push_back(side);
	texture.push_back(side);


	loadTexture();
}

Texture3D::Texture3D(const string& front, const string& back, const string& right, const string& left, const string& top, const string& bottom)
	: mTexture(0)
{
	texture.push_back(right);
	texture.push_back(left);
	texture.push_back(top);
	texture.push_back(bottom);
	texture.push_back(front);
	texture.push_back(back);


	loadTexture();
}

Texture3D::~Texture3D() {}

bool Texture3D::loadTexture(bool generateMipMaps)
{
	glEnable(GL_TEXTURE_CUBE_MAP);

	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTexture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);

	unsigned char* data;
	int width, height, components;

	for (int i = 0; i < 6; i++) {

		data = stbi_load(texture[i].c_str(), &width, &height, &components, STBI_rgb_alpha);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	if (generateMipMaps)
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	stbi_image_free(data); //free memory
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0); //unbind texture

	return true;
}

void Texture3D::bind(GLuint texUnit)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTexture);
}