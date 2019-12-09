#pragma once


#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "glm/glm.h"

using namespace std;


struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

//Texture data will be stored in this struct
//Store ID
struct Texture {
	unsigned int id;
	string type;

};

class Mesh {
public:
//Mesh
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader shader);
private:
	void setupMesh();
	
//render data
	unsigned int VAO, VBO, EBO;
};

Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {

	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	//vertex texture coordinates
	glEnableVertexAtrribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);

}

/*
	// Range of texture samples
	//As many textures as we want can be defined.

	uniform sampler2D texture_diffuse1;
	uniform sampler2D texture_diffuse2;
	uniform sampler2D texture_diffuse3;
	uniform sampler2D texture_specular1;
	uniform sampler2D texture_specular2;


*/


void Draw(Shader shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{

		//activate proper texture unit before binding
		glActiveTexture(GL_TEXTURE0 + i);

		// retrieve texture number (the N in diffuse_textureN)
		string number;
		string name = textures[i].type;

		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}