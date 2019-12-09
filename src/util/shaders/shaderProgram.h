#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H


#include <string>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include <map>

using namespace std;
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

	bool loadShaders(const char* vertex_shaderFilename, const char* fragment_shaderFilename);
	void use();
	void setUniform(const GLchar* name, const glm::vec2 &v);
	void setUniform(const GLchar* name, const glm::vec3 &v);
	void setUniform(const GLchar* name, const glm::vec4 &v);
	void setUniform(const GLchar* name, const glm::mat4 &m);


private:

	string fileToString(const string &filename);
	void checkCompileErrors(GLuint shader, ShaderType type);
	GLint getUniformLocation(const GLchar *name);

	GLuint mHandle;
	std::map<string, GLint> mUniformLocations; //map to hold the uniform locations

};

#endif //SHADER_PROGRAM_H