#pragma once

#include <unordered_map>

#include <glm/gtc/matrix_transform.hpp>

#include <world/chunks/Chunk.h>
//#include <world/blocks/AirBlock.h>
#include <player/Player.h>
//#include <world/environment/Skybox.h>

class World {
public:

	enum Direction {
		NORTH,
		EAST,
		SOUTH,
		WEST,
		UP,
		DOWN,
		ORIGIN
	};

	
	static World* getInstance() {
		static World* instance = new World();
		return instance;
	}

	/*
	World()
	{
	}

	void addPlayer(string name, FPSCamera* fpsCam, float width, float height, GLFWwindow* window)
	{
		player = new Player("TestPlayer", fpsCam, this, true, width, height, window);

		renderDistance = player->getRenderDistance();
		chunkPos = getChunkFromPos(player->getPos());
		update(0);
		generateSurrounding();
	}
	*/

	/*
	bool findChunk(const glm::ivec3 &pos) {
		if (chunks.find(ivec3_hash(pos)) != chunks.end())
			return true;

		return false;
	}
	*/

	glm::ivec3 getChunkFromPos(const glm::vec3 &pos) {
		glm::ivec3 temp_chunkPos;

		temp_chunkPos.x = floor(pos.x / 16);
		temp_chunkPos.x *= 16;	

		temp_chunkPos.y = floor(pos.y / 16);
		temp_chunkPos.y *= 16;

		temp_chunkPos.z = floor(pos.z / 16);
		temp_chunkPos.z *= 16;

		return temp_chunkPos;
	}

	/*
	unsigned char getBlockFromPos(const string& username) {
		PlayerChunks pc = players[username];

		return pc.chunks[ivec3_hash(pc.chunkPos)]->getBlock(pc.playerPos);
	}
	*/

	Block* getBlock(const string &username, const glm::vec3 &lookAt, const glm::vec3 &look) {
		glm::ivec3 targetPos;
		
		for (float i = 1; i <= 3.0; i += 0.25) {
			
			targetPos.x = floor(lookAt.x + look.x * i);
			targetPos.y = floor(lookAt.y + look.y * i);
			targetPos.z = floor(lookAt.z + look.z * i);

			//cout << "chunk pos" << endl;
			//cout << getChunkFromPos(targetPos).x << " " << getChunkFromPos(targetPos).y << " " << getChunkFromPos(targetPos).z << endl;
			//cout << "target pos" << endl;
			//cout << targetPos.x << " " << targetPos.y << " " << targetPos.z << endl;

			if (players[username].chunks[ivec3_hash(getChunkFromPos(targetPos))]->getBlock(targetPos) == 0) 
			{
				continue;
			}

			return Chunk::getBlock(players[username].chunks[ivec3_hash(getChunkFromPos(targetPos))]->getBlock(targetPos));
		}

		return AirBlock::getInstance();
	}

	void breakBlock(unordered_map<int, Chunk*> &chunks, const glm::vec3& lookAt, const glm::vec3& look) {
		glm::ivec3 targetPos;

		for (float i = 1; i <= 3.0; i += 0.25) {

			targetPos.x = floor(lookAt.x + look.x * i);
			targetPos.y = floor(lookAt.y + look.y * i);
			targetPos.z = floor(lookAt.z + look.z * i);

			if (chunks[ivec3_hash(getChunkFromPos(targetPos))]->getBlock(targetPos) == 0)
			{
				continue;
			}

			chunks[ivec3_hash(getChunkFromPos(targetPos))]->setBlock(targetPos, 0);
			return;
		}
	}

	void update(const string &username, const double &et) {
		update(players[username], et);
	}

	void addPlayer(Player* player) {
		PlayerChunks pc;
		pc.player = player;
		pc.moving = Direction::ORIGIN;
		update(pc, 0);
		generateSurrounding(pc.chunks, pc.chunkPos, pc.player->getRenderDistance());
		generateSurrounding(pc.chunks, pc.chunkPos, pc.player->getRenderDistance(), -16, 0);

		pc.chunks[ivec3_hash(glm::ivec3(0, -16, 0))] = new Chunk(glm::ivec3(0, -16, 0));

		players[player->getName()] = pc;
	}

	void render(string username, ShaderProgram &shader) {

		for (auto chunk : players[username].chunks) {
			chunk.second->renderChunk(shader);
		}
	}

private:

	struct PlayerChunks {
		Player* player;
		unordered_map<int, Chunk*> chunks;
		Direction moving;
		glm::ivec3 chunkPos;
		glm::vec3 playerPos;
	};

	unordered_map<string, PlayerChunks> players;

	World() {}

	void update(PlayerChunks &pc, const double & et) {
		if (pc.player->update(et, pc.chunks[ivec3_hash(pc.chunkPos)] == NULL ? 1 : getBlockFromPos(pc))) { //floor: negs round to 0
			breakBlock(pc.chunks, pc.player->getLookAt(), pc.player->getLook());
		}

		if (pc.player->getPos() != pc.playerPos) {
			pc.playerPos = pc.player->getPos();

			if (getChunkFromPos(pc.playerPos, pc.chunkPos, pc.moving)) {
				pruneChunks(pc.chunks, pc.chunkPos, pc.moving, pc.player->getRenderDistance());
			}
		}

		//pc.player->checkBounds(pc.chunks[ivec3_hash(pc.chunkPos)] == NULL ? 1 : getBlockFromPos(pc));
	}

	unsigned char getBlockFromPos(PlayerChunks &pc) {
		return pc.chunks[ivec3_hash(pc.chunkPos)]->getBlock(glm::ivec3(floor(pc.playerPos.x), floor(pc.playerPos.y), floor(pc.playerPos.z)));
	}

	bool getChunkFromPos(glm::vec3 playerPos, glm::ivec3 &chunkPos, Direction &moving) {
		int temp = floor(playerPos.x / 16);
		temp *= 16;
		if (temp != chunkPos.x) {
			if (temp > chunkPos.x)
				moving = Direction::NORTH;
			else
				moving = Direction::SOUTH;
			chunkPos.x = temp;
			return true;
		}

		temp = floor(playerPos.y / 16);
		temp *= 16;
		if (temp != chunkPos.y) {
			if (temp > chunkPos.y)
				moving = Direction::UP;
			else
				moving = Direction::DOWN;
			chunkPos.y = temp;
			return true;
		}

		temp = floor(playerPos.z / 16);
		temp *= 16;
		if (temp != chunkPos.z) {
			if (temp > chunkPos.z)
				moving = Direction::EAST;
			else
				moving = Direction::WEST;
			chunkPos.z = temp;
			return true;
		}

		moving = Direction::ORIGIN;
		return false;
	}

	void pruneChunks(unordered_map<int, Chunk*>& chunks, const glm::ivec3 chunkPos, Direction& moving, const unsigned short& renderDistance, int level = 0) {
		switch (moving) {
		case NORTH:
			for (short i = renderDistance * -1; i <= renderDistance; i++) {

				/*
				cout << "Erasing..." << endl;
				cout << chunkPos.x - 16 * (renderDistance + 1) << " " << 0 << " " << i * 16 + chunkPos.z << " = " <<
					ivec3_hash(glm::ivec3(glm::ivec3(chunkPos.x - 16 * (renderDistance + 1), 0, i * 16 + chunkPos.z))) << endl;
				*/

				//erase chunks past render distance
				chunks.erase(ivec3_hash(glm::ivec3(chunkPos.x - 16 * (renderDistance + 1), level, i * 16 + chunkPos.z)));

				/*
				cout << "Adding..." << endl;
				cout << chunkPos.x + renderDistance * 16 << " " << 0 << " " << i * 16 + chunkPos.z << " = " <<
					ivec3_hash(glm::ivec3(chunkPos.x + renderDistance * 16, 0, i * 16 + chunkPos.z)) << endl;
				*/

				//add chunks at render distance
				chunks[ivec3_hash(glm::ivec3(chunkPos.x + renderDistance * 16, level, i * 16 + chunkPos.z))]
					= new Chunk(glm::ivec3(chunkPos.x + renderDistance * 16, level, i * 16 + chunkPos.z));
			}
			//cout << "================================================" << endl;
			return;

		case EAST:
			for (short i = renderDistance * -1; i <= renderDistance; i++) {
				chunks.erase(ivec3_hash(glm::ivec3(i * 16 + chunkPos.x, level, chunkPos.z - 16 * (renderDistance + 1))));

				chunks[ivec3_hash(glm::ivec3(i * 16 + chunkPos.x, level, chunkPos.z + renderDistance * 16))]
					= new Chunk(glm::ivec3(i * 16 + chunkPos.x, level, chunkPos.z + renderDistance * 16));
			}
			return;

		case SOUTH:
			for (short i = renderDistance * -1; i <= renderDistance; i++) {
				chunks.erase(ivec3_hash(glm::ivec3(chunkPos.x + 16 * (renderDistance + 1), level, i * 16 + chunkPos.z)));

				chunks[ivec3_hash(glm::ivec3(chunkPos.x - renderDistance * 16, level, i * 16 + chunkPos.z))]
					= new Chunk(glm::ivec3(chunkPos.x - renderDistance * 16, level, i * 16 + chunkPos.z));
			}
			return;

		case WEST:
			for (short i = renderDistance * -1; i <= renderDistance; i++) {
				chunks.erase(ivec3_hash(glm::ivec3(i * 16 + chunkPos.x, level, chunkPos.z + 16 * (renderDistance + 1))));

				chunks[ivec3_hash(glm::ivec3(i * 16 + chunkPos.x, level, chunkPos.z - renderDistance * 16))]
					= new Chunk(glm::ivec3(i * 16 + chunkPos.x, level, chunkPos.z - renderDistance * 16));
			}
			return;
		}
	}

	void generateSurrounding(unordered_map<int, Chunk*> &chunks, const glm::ivec3 &chunkPos, const unsigned short &renderDistance, int level = 0, int genType = -1) {
		for (short i = renderDistance * -1; i <= renderDistance; i++) {
			for (short j = renderDistance * -1; j <= renderDistance; j++) {
				chunks[ivec3_hash(glm::ivec3(i * 16 + chunkPos.x, level, j * 16 + chunkPos.z))]
					  = new Chunk(glm::ivec3(i * 16 + chunkPos.x, level, j * 16 + chunkPos.z), genType);
			}
		}
	}

	int ivec3_hash(glm::ivec3 pos) {
		return pos.x * 1013 + pos.y * 907 + pos.z * 809;
	}
};