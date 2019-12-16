#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "world/blocks/Block.h"
#include "world/blocks/GrassBlock.h"
#include "world/blocks/DirtBlock.h"
#include "world/blocks/AirBlock.h"

#include "util/shaders/shaderProgram.h"
#include "world/chunks/newMesh.h"


class Chunk {
public:

	GLuint VAO;

	Chunk(glm::ivec3 pos)
		:chunkPos(pos)
	{
		mat_chunkPos = glm::translate(glm::mat4(1), glm::vec3(chunkPos));
		generateChunk();
	}


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

	unsigned int getBlock(glm::ivec3 pos) {
		pos.x %= 16;
		pos.y %= 16;
		pos.z %= 16; 

		if (chunkPos.x < 0 && chunkPos.y < 0 && chunkPos.z < 0) {
			return blocks[pos.x < 0 ? 16 - pos.x * -1 : 16 - pos.x]
						 [pos.y < 0 ? 16 - pos.y * -1 : 16 - pos.y]
						 [pos.z < 0 ? 16 - pos.z * -1 : 16 - pos.z];
		}
		else
		if (chunkPos.x < 0 && chunkPos.y < 0) {
			return blocks[pos.x < 0 ? 16 - pos.x * -1 : 16 - pos.x]
							[pos.y < 0 ? 16 - pos.y * -1 : 16 - pos.y]
							[pos.z < 0 ? pos.z * -1 : pos.z];
		}
		else
		if (chunkPos.x < 0 && chunkPos.z < 0) {
			return blocks[pos.x < 0 ? 16 - pos.x * -1 : 16 - pos.x]
						 [pos.y < 0 ? pos.y * -1 : pos.y]
						 [pos.z < 0 ? 16 - pos.z * -1 : 16 - pos.z];
		}
		else
		if (chunkPos.y < 0 && chunkPos.z < 0) {
			return blocks[pos.x < 0 ? pos.x * -1 : pos.x]
					   	 [pos.y < 0 ? 16 - pos.y * -1 : 16 - pos.y]
						 [pos.z < 0 ? 16 - pos.z * -1 : 16 - pos.z];
		}
		else
		if (chunkPos.x < 0) {
			return blocks[pos.x < 0 ? 16 - pos.x * -1 : 16 - pos.x]
						 [pos.y < 0 ? pos.y * -1 : pos.y]
						 [pos.z < 0 ? pos.z * -1 : pos.z];
		}
		else
		if (chunkPos.y < 0) {
			return blocks[pos.x < 0 ? pos.x * -1 : pos.x]
						 [pos.y < 0 ? 16 - pos.y * -1 : 16 - pos.y]
						 [pos.z < 0 ? pos.z * -1 : pos.z];
		}
		else
		if (chunkPos.z < 0) {
			return blocks[pos.x < 0 ? pos.x * -1 : pos.x]
						 [pos.y < 0 ? pos.y * -1 : pos.y]
						 [pos.z < 0 ? 16 - pos.z * -1 : 16 - pos.z];
		}
		else {
			return blocks[pos.x < 0 ? pos.x * -1 : pos.x]
						 [pos.y < 0 ? pos.y * -1 : pos.y]
						 [pos.z < 0 ? pos.z * -1 : pos.z];
		}
	}

	void setBlock(glm::ivec3 pos, unsigned int block) {
		pos.x %= 16;
		pos.y %= 16;
		pos.z %= 16;

		if (chunkPos.x < 0 && chunkPos.y < 0 && chunkPos.z < 0) {
			blocks[pos.x < 0 ? 16 - pos.x * -1 : 16 - pos.x]
				  [pos.y < 0 ? 16 - pos.y * -1 : 16 - pos.y]
				  [pos.z < 0 ? 16 - pos.z * -1 : 16 - pos.z] = block;
		}
		else
		if (chunkPos.x < 0 && chunkPos.y < 0) {
			blocks[pos.x < 0 ? 16 - pos.x * -1 : 16 - pos.x]
				  [pos.y < 0 ? 16 - pos.y * -1 : 16 - pos.y]
				  [pos.z < 0 ? pos.z * -1 : pos.z] = block;
		}
		else
		if (chunkPos.x < 0 && chunkPos.z < 0) {
			blocks[pos.x < 0 ? 16 - pos.x * -1 : 16 -pos.x]
				  [pos.y < 0 ? pos.y * -1 : pos.y]
				  [pos.z < 0 ? 16 - pos.z * -1 : 16 - pos.z] = block;
		}
		else
		if (chunkPos.y < 0 && chunkPos.z < 0) {
			blocks[pos.x < 0 ? pos.x * -1 : pos.x]
				  [pos.y < 0 ? 16 - pos.y * -1 : 16 - pos.y]
				  [pos.z < 0 ? 16 - pos.z * -1 : 16 - pos.z] = block;
		}
		else
		if (chunkPos.x < 0) {
			blocks[pos.x < 0 ? 16 - pos.x * -1 : 16 - pos.x]
				  [pos.y < 0 ? pos.y * -1 : pos.y]
				  [pos.z < 0 ? pos.z * -1 : pos.z] = block;
		}
		else
		if (chunkPos.y < 0) {
			blocks[pos.x < 0 ? pos.x * -1 : pos.x]
				  [pos.y < 0 ? 16 - pos.y * -1 : 16 - pos.y]
				  [pos.z < 0 ? pos.z * -1 : pos.z] = block;
		}
		else
		if (chunkPos.z < 0) {
				blocks[pos.x < 0 ? pos.x * -1 : pos.x]
					  [pos.y < 0 ? pos.y * -1 : pos.y]
					  [pos.z < 0 ? 16 - pos.z * -1 : 16 - pos.z] = block;
		}
		else {
			blocks[pos.x < 0 ? pos.x * -1 : pos.x]
				  [pos.y < 0 ? pos.y * -1 : pos.y]
				  [pos.z < 0 ? pos.z * -1 : pos.z] = block;
		}
	}

	/*
	Block* getBlock(glm::ivec3 pos) {
		pos.x %= 16;
		pos.y %= 16;
		pos.z %= 16;

		return getBlock(blocks[ pos.x < 0 ? pos.x * -1 : pos.x ]
							  [ pos.y < 0 ? pos.y * -1 : pos.y ]
							  [ pos.z < 0 ? pos.z * -1 : pos.z ]);
	}
	*/

	glm::ivec3 getChunkPos() {
		return chunkPos;
	}
	//Rendering blocks
	void renderChunk(ShaderProgram &shaderProgram) {
		unsigned char lastBlockId = NULL;

		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				for (int k = 0; k < 16; k++) {

					if (blocks[i][j][k] == 0) // block of air.
						continue;



					if (blocks[i][j][k] != lastBlockId) { //Makes sure that you dont have to change texture, only bindsTexture if it needs to change texture
						getBlock(blocks[i][j][k])->bindTexture();
					}

					shaderProgram.setUniform("model", glm::translate(mat_chunkPos, glm::vec3(i, j, k)));
					

					//cull faces if there's a block next to this one (needs a reference to World.getBlock to work correctly.)
					if (getBlock(glm::ivec3(i, j, k + 1)) == 0)

						glBindVertexArray(this->VAO);
						
						glDrawArrays(GL_TRIANGLES, 0, 6); 
					if (getBlock(glm::ivec3(i, j, k - 1)) == 0) 
						glBindVertexArray(this->VAO);

						glDrawArrays(GL_TRIANGLES, 6, 6);
					if (getBlock(glm::ivec3(i - 1, j, k)) == 0) //Y axis
					//	glBindVertexArray(this->VAO);//

					  glDrawArrays(GL_TRIANGLES, 12, 6);
					if (getBlock(glm::ivec3(i + 1, j, k)) == 0) //Y Axis
						//glBindVertexArray(this->VAO);//

					 glDrawArrays(GL_TRIANGLES, 18, 6);
					if (getBlock(glm::ivec3(i, j + 1, k)) == 0) //Top Down grass
						glBindVertexArray(this->VAO);

						glDrawArrays(GL_TRIANGLES, 24, 6);
					if (getBlock(glm::ivec3(i, j - 1, k)) == 0) //BOTTOM DIRT
						//glBindVertexArray(this->VAO); //

					glDrawArrays(GL_TRIANGLES, 30, 6);
					//glDrawArrays(GL_TRIANGLES, 0, 36);
					
				}
			}
		}
	}

private:

	glm::ivec3 chunkPos;
	glm::mat4 mat_chunkPos;

	unsigned char blocks[16][16][16] = { 0 };


	
	void generateChunk() {
		if (chunkPos.y == 0) { //0 height = airblock
			for (int i = 0; i < 16; i++) { //indexes of array are the chunks position to plane
				for (int k = 0; k < 16; k++) {

					blocks[i][0][k] = 1;
				}
			}

			if (chunkPos == glm::ivec3(0, 0, 0)) {
				blocks[8][1][8] = 2;
				blocks[8][2][8] = 2;
				blocks[8][3][8] = 2;
				blocks[8][2][7] = 2;
				blocks[8][2][9] = 2;
				blocks[7][2][8] = 2;
				blocks[9][2][8] = 2;
			}
		}
		else {
			for (int i = 0; i < 16; i++) {
				for (int j = 0; j < 16; j++) {
					for (int k = 0; k < 16; k++) {
						blocks[i][j][k] = 2;
					}
				}
			}
		}
	}
};