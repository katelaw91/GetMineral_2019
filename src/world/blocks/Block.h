#pragma once

#include "util/textures/texture2D.h"
//#include "GrassBlock.h"
//#include "DirtBlock.h"
//#include "AirBlock.h"

static const GLfloat vertices[] = {
	//position X, Y, Z     //texture coords

	// front face
	-0.5f,  0.5f,  0.5f,	
	 0.5f, -0.5f,  0.5f,	
	 0.5f,  0.5f,  0.5f,	
	-0.5f,  0.5f,  0.5f,	
	-0.5f, -0.5f,  0.5f,	
	 0.5f, -0.5f,  0.5f,	

	 // back face
	 -0.5f,  0.5f, -0.5f,	
	  0.5f,  0.5f, -0.5f,	
	  0.5f, -0.5f, -0.5f,	
	 -0.5f, -0.5f, -0.5f,	
	 -0.5f,  0.5f, -0.5f,	
	  0.5f, -0.5f, -0.5f,	

	  // left face
	  -0.5f,  0.5f, -0.5f,	
	  -0.5f, -0.5f,  0.5f,	
	  -0.5f,  0.5f,  0.5f,	
	  -0.5f,  0.5f, -0.5f,	
	  -0.5f, -0.5f, -0.5f,	
	  -0.5f, -0.5f,  0.5f,	

	  // right face
	   0.5f,  0.5f,  0.5f,	
	   0.5f, -0.5f, -0.5f,	
	   0.5f,  0.5f, -0.5f,	
	   0.5f,  0.5f,  0.5f,	
	   0.5f, -0.5f,  0.5f,	
	   0.5f, -0.5f, -0.5f,	

	   // top face
	   -0.5f,  0.5f, -0.5f,	
		0.5f,  0.5f,  0.5f,	
		0.5f,  0.5f, -0.5f,	
	   -0.5f,  0.5f, -0.5f, 
	   -0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 

		// bottom face
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
};

class Block {
public:

	virtual void bindTexture() = 0;

	virtual unsigned char getIdFromBlock() = 0;

	static const GLfloat* const getVertices() {
		return vertices;
	}

	static const unsigned int getSize() {
		return sizeof(vertices);
	}

	/*
	static Block* getBlock(unsigned char id) {
		switch (id) {
		default:
		case 0:
			return AirBlock::getInstance();
		case 1:
			return GrassBlock::getInstance();
		case 2:
			return DirtBlock::getInstance();
		}
	}
	*/
};