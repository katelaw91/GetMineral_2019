#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include <string>
#include <vector>

using namespace std;
class Texture2D
{
public:
	Texture2D();
	Texture2D(const string& filename);
	Texture2D(const string& side, const string& top);
	Texture2D(const string& side, const string& top, const string& bottom);
	Texture2D(const string& front, const string& back, const string& right, const string& left, const string& top, const string& bottom);
	virtual ~Texture2D();

	bool loadTexture(bool generateMipMaps = true);
	void bind(GLuint texUnit = 0);

private:

	GLuint mTexture;
	std::vector<string> texture;
};

#endif // end TEXTURE_H