#pragma once

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <util/shaders/shaderProgram.h>
//#include "vertex.h"

using namespace std;


struct Vertex
{
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords; 
};

struct Texture
{
  GLuint id;
  string type;
  //aiString path;
};

class Mesh
{
 public:
  vector<Vertex> vertices; //corners of an object
   vector<GLuint> indices;
  vector<Texture> textures;

  Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures ) //Constructor
    { //passing data from the vertices, indices, textures and assigning it to the mesh's variable.
      this->vertices = vertices;
      this->indices = indices;
      this->textures = textures;
      //now we can set the vertex buffers and the attribute pointers.

      this->SetupMesh();
    }

  /*
  Mesh(glm::vec3 Position, glm::vec3 Normal, glm::vec2 TexCoords)
  {
	  Vertices vert;
	  vert.Position = Positon;


	  this->vertices = vertices;
	  this->indices = indices;
	  this->textures = textures;

	  this->SetupMesh();
  }
  */

  //draw method
  void Draw(ShaderProgram shader)
  {
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;

    for(GLuint i = 0; i < this->textures.size(); i++)
      {
	//set the active texture
	glActiveTexture(GL_TEXTURE0 + i);
	//retrieve the texture number
	stringstream ss;
	string number;
	string name = this->textures[i].type;
	//check if name is texture diffuse or specular

	if("texture_diffuse" == name)
	  {
	    ss << diffuseNr++; //input into stringStream (Diffuse) and increment it
	  }
	else
		if ("texture_specular" == name)
	  {
	    ss << specularNr++; //input into stringStream (Specular) and increment it
	  }

	number = ss.str(); //will getstring from string stream
	//glUniform1i(glGetUniformLocation(shader.program, (name + number), c_str()), i); //Will set the sampler to the correct texture unit
	glBindTexture(GL_TEXTURE_2D, this->textures[i].id); //bind the textures
       }

    //set each mesh's shinness property value to a default value
   // glUniform1f(glGetUniformLocation(shader.program, "Material.shininess"), 16.0f );

    //draw mesh
    glBindVertexArray(this->VAO); //(Vertex Array Object)
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    //unbind vertex array
    glBindVertexArray(0);
    //set everything back to result value
    for(GLuint i = 0; i < this->textures.size(); i++)
      {
	glActiveTexture(GL_TEXTURE0 + i);
	//bind texture
	glBindTexture(GL_TEXTURE_2D, 0);
      }
   }

 private:
  GLuint VAO, VBO, EBO;
  //initialize buffer objects and arrays
  void SetupMesh()
  {
    glGenVertexArrays(1, &this->VAO); //(Vertex Array Object)
    glGenBuffers(1, &this->VBO); //(Vertex Buffer Object)
    glGenBuffers(1, &this->EBO); //(Element Buffer Object)
    
    glBindVertexArray(this->VAO);
    //load data into the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    //buffer data, gaining the size of the vertices
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
    //bind the buffer from the element buffer object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    //buffer data, gaining the size of the vertices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid * )0 );
    //vertex normals
    glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid * )offsetof(Vertex, Normal) );

    //vertex texture coordinates
    glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid * )offsetof(Vertex, TexCoords) );
    glBindVertexArray(0);
  }

  
};





















/*

class Mesh {
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	

	void initVertexData(Vertex* vertexArray, const unsigned nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndicies)
	{
		//Initialize vertex data
		for(size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertexArray[i]);
		}

		for (size_t i = 0; i < nrOfIndicies; i++)
		{
			this->vertices.push_back(indexArray[i]);
		}


	}

	void initVAO()
	{
		GLuint VAO;
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA

		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW); //sending in raw data that is in

		//GEN EBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offset);
		glEnableVertexAttribArray(0);
		//Color
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offset)
		glEnableVertexAttribArray(1);



	}

	void intitModelMatrix()
	{

	}


public:
	Mesh(Vertex* vertexArray, const unsigned nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndicies)
	{
		
		this->initVertexData(vertexArray, nrOfVertices, indexArray, nrOfIndicies);
		this->initVAO;
		this->intitModelMatrix;

	}
	~Mesh()
	{

	}

	void update()
	{

	}
	void render(ShaderProgram shader)
	{

	}

};
*/
