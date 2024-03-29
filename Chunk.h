#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "world/blocks/Block.h"
#include "world/blocks/GrassBlock.h"
#include "world/blocks/DirtBlock.h"
#include "world/blocks/AirBlock.h"
//#include "world/chunks/SimplexNoise.h"
//#include "world/chunks/PerlinNoise.h"
#include "Terrain.h"

#include "util/shaders/shaderProgram.h"

using namespace std;

class Chunk {
public:

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

		if (chunkPos.x > 0 && chunkPos.y > 0 && chunkPos.z > 0) {
			return blocks[pos.x < 0 ? pos.x * -1 : pos.x]
						 [pos.y < 0 ? pos.y * -1 : pos.y]
						 [pos.z < 0 ? pos.z * -1 : pos.z];
		}
		else
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

		if (chunkPos.x > 0 && chunkPos.y > 0 && chunkPos.z > 0) {
			blocks[pos.x < 0 ? pos.x * -1 : pos.x]
				  [pos.y < 0 ? pos.y * -1 : pos.y]
				  [pos.z < 0 ? pos.z * -1 : pos.z] = block;
		}
		else
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

	void renderChunk(ShaderProgram &shaderProgram) {
		unsigned char lastBlockId = NULL;

		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				for (int k = 0; k < 16; k++) {

					if (blocks[i][j][k] == 0)
						continue;

					if (blocks[i][j][k] != lastBlockId) {
						getBlock(blocks[i][j][k])->bindTexture();
					}

					shaderProgram.setUniform("model", glm::translate(mat_chunkPos, glm::vec3(i, j, k)));
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}
		}
	}

private:

	glm::ivec3 chunkPos;
	glm::mat4 mat_chunkPos;

	unsigned char blocks[16][16][16] = { 0 };

	void generateChunk() {
		unsigned noiseValues[16][16];
		float offset = .2;
		float perlinValue;
		int maxHeight = 16;
		int ry, rx, rz;
		Perlin p;


		if (chunkPos.y == 0) {
			for (int x = 0; x < 16; x++) {
				int n = (p.fPerlinNoise1D[x] * (float)16);
				//rx = rand() % 16;
				for (int y = 0; y < 16; y++) {
					//ry = rand() % 16;
					for (int z = 0; z < 16; z++){
						//rz = rand() % 16;
						//octave_noise_3d(3.0, 0.5, 1, x, y, z) >> endl;
						blocks[x][n][z] = 1;
						int temp = n - 1;
						while (temp > 0) {
							blocks[x][temp][z] = 2;
							temp--;

						}

						//add balls lol
						if (sqrt((float)(x - 16 / 2)*(x - 16 / 2) + (y - 16 / 2)*(y - 16 / 2) + (z - 16 / 2)*(z - 16 / 2)) <= 16 / 2)
						{
							blocks[x][y][z] = 1;
						}
						/*if (ry > 12) {
							blocks[rx][ry][rz] = 1;
						}
						else {
							blocks[rx][ry][rz] = 2;
							blocks[x][0][z] = 1;
						}*/
						//n = n + offset;
						//perlin = (int)n % 16;
						//blocks[x][y][z] = 1;
					}
				}
			}


	

			

			if (chunkPos == glm::ivec3(0, 0, 0)) {
				blocks[0][1][0] = 2;
				blocks[0][2][0] = 2;
				blocks[0][3][0] = 2;
				blocks[2][1][0] = 2;
				blocks[2][2][0] = 2;
				blocks[2][3][0] = 2;
				blocks[2][4][0] = 2;

				
				/*for (int i = 0; i < 16; i++) {
					n = n + offset;
					int rx = (int)n % 16;
					//int rx = rand() % 10;

					for (int j = 0; j < 16; j++) {
						n = n + offset;
						int ry = (int)n % 16 ;
						//int ry = rand() % 10;

						for (int k = 0; k < 16; k++) {
							n = n + offset;
							int rz = (int)n % 16;
							//int rz = rand() % 10;
							
							if(blocks[rx][ry + 1][rz] == 2)
							{
								blocks[rx][ry][rz] == 1;
							}
							else {
								blocks[rx][ry][rz] = 2;
							}
						}
					}
				}*/


			}
		}
		
		/*else {
		
			for (int i = 0; i < 16; i++) {
				for (int j = 0; j < 16; j++) {
					for (int k = 0; k < 16; k++) {
						
						//blocks[i][j][k] = 2;

					//change here for every chunk beside y = 0
					//to generate a single chunk uncommment line 130 in World.h
					//comment out generateSurrounding(pc.chunks, pc.chunkPos, pc.player->getRenderDistance()); in World.h on line 131
					//also comment out pruneChunks(pc.chunks, pc.chunkPos, pc.moving, pc.player->getRenderDistance()); on line 187

						if ((i % 4 == 0 && j > 12) || j <= 12) {
							blocks[i][j][k] = 2;
						}
						else
							if ((i % 4 == 1 || i % 4 == 3) && j <= 14) {
								blocks[i][j][k] = 1;
							}
							else
								if (i % 4 == 2 && j <= 13) {
									blocks[i][j][k] = 1;
								}
								else
									blocks[i][j][k] = 0;

						if (j == 15 && blocks[i][j][k] == 2)
							blocks[i][j][k] = 1;
					}
				}
			}
		}*/
	}
};