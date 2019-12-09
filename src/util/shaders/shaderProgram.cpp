#include "shaderProgram.h"
#include <fstream> //load shader from file
#include <iostream>
#include <sstream>
#include "glm/gtc/type_ptr.hpp"



ShaderProgram::ShaderProgram()
	: mHandle(0)
{
}


ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(mHandle);
}

bool ShaderProgram::loadShaders(const char* vertex_shaderFilename, const char* fragment_shaderFilename)
{

	string vertex_shaderString = fileToString(vertex_shaderFilename);
	string fragment_shaderString = fileToString(fragment_shaderFilename);
	const GLchar* vertex_shaderSourcePtr = vertex_shaderString.c_str();
	const GLchar* fragment_shaderSourcePtr = fragment_shaderString.c_str();



	//create shaders
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader, 1, &vertex_shaderSourcePtr, NULL);
	glShaderSource(fragment_shader, 1, &fragment_shaderSourcePtr, NULL);

	//compile shaders
	glCompileShader(vertex_shader);
	checkCompileErrors(vertex_shader, VERTEX);
	glCompileShader(fragment_shader);
	checkCompileErrors(fragment_shader, FRAGMENT);


	//create shader program
	mHandle = glCreateProgram();

	//attach shaders to program
	glAttachShader(mHandle, vertex_shader);
	glAttachShader(mHandle, fragment_shader);

	//link compiled shaders into a single program
	glLinkProgram(mHandle);
	checkCompileErrors(mHandle, PROGRAM);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	mUniformLocations.clear();

	return true;
}
void ShaderProgram::use()
{
	if (mHandle > 0)
		glUseProgram(mHandle);
}

string ShaderProgram::fileToString(const string &filename)
{
	stringstream ss;
	ifstream file;

	try
	{
		file.open(filename, ios::in);
		if (!file.fail())
		{
			ss << file.rdbuf();
		}
		file.close();
	}
	catch (exception ex)
	{
		cerr << "Error reading shader filename." << endl;
	}

	return ss.str();
}

void ShaderProgram::checkCompileErrors(GLuint shader, ShaderType type)
{
	int status = 0;

	if (type == PROGRAM)
	{
		glGetProgramiv(mHandle, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint length = 0;
			glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &length);

			string errorLog(length, ' ');
			glGetProgramInfoLog(mHandle, length, &length, &errorLog[0]);
			cerr << "Program failed to link: " << errorLog << endl;
		}
	}

	else //VERTEX or FRAGMENT
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			string errorLog(length, ' ');
			glGetShaderInfoLog(shader, length, &length, &errorLog[0]);
			cerr << "Shader failed to link compile: " << errorLog << endl;
		}
	}
}

GLint ShaderProgram::getUniformLocation(const GLchar *name)
{
	std::map<string, GLint>::iterator it = mUniformLocations.find(name); //check to see if already exists

	if (it == mUniformLocations.end()) //if end of array without finding uniform loc
	{
		mUniformLocations[name] = glGetUniformLocation(mHandle, name); //add
	}

	return mUniformLocations[name];
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec2 &v)
{
	GLint loc = getUniformLocation(name);
	glUniform2f(loc, v.x, v.y);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec3 &v)
{
	GLint loc = getUniformLocation(name);
	glUniform3f(loc, v.x, v.y, v.z);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::vec4 &v)
{
	GLint loc = getUniformLocation(name);
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::mat4 &m)
{
	//GLint loc = getUniformLocation(name);
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(m));
}