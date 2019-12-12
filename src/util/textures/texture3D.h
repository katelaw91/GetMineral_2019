#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include <string>
#include <vector>

using namespace std;
class Texture3D
{
public:
	Texture3D();
	Texture3D(const string& filename);
	Texture3D(const string& side, const string& top);
	Texture3D(const string& side, const string& top, const string& bottom);
	Texture3D(const string& front, const string& back, const string& right, const string& left, const string& top, const string& bottom);
	virtual ~Texture3D();

	bool loadTexture(bool generateMipMaps = true);
	void bind(GLuint texUnit = 0);

private:

	GLuint mTexture;
	std::vector<string> texture;
};

#endif // end TEXTURE_H