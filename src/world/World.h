#include <unordered_map>

#include <glm/gtc/matrix_transform.hpp>

#include <world/chunks/Chunk.h>
//#include <world/blocks/AirBlock.h>
//#include <player/Player.h>
//#include <world/environment/Skybox.h>

class World {
public:

	static World* getInstance() {
		static World* instance = new World();
		return instance;
	}

	/*
	bool findChunk(const glm::ivec3 &pos) {
		if (chunks.find(ivec3_hash(pos)) != chunks.end())
			return true;

		return false;
	}
	*/

	glm::ivec3 getChunkFromPos(const glm::vec3 &pos) {
		glm::ivec3 temp_chunkPos;

		int temp = pos.x / 16;
		if (pos.x < 0)
			temp--;
		temp_chunkPos.x = temp * 16;	

		temp = pos.y / 16;
		if (pos.y < 0)
			temp--;
		temp_chunkPos.y = temp * 16;

		temp = pos.z / 16;
		if (pos.z < 0)
			temp--;
		temp_chunkPos.z = temp * 16;

		return temp_chunkPos;
	}

	Block* getBlock(const glm::vec3 &lookAt, const glm::vec3 &look) {
		glm::ivec3 targetPos;
		
		for (float i = 1; i <= 3.0; i += 0.25) {
			
			targetPos.x = lookAt.x + look.x * i;
			targetPos.y = lookAt.y + look.y * i;
			targetPos.z = lookAt.z + look.z * i;

			//cout << "chunk pos" << endl;
			//cout << getChunkFromPos(targetPos).x << " " << getChunkFromPos(targetPos).y << " " << getChunkFromPos(targetPos).z << endl;
			//cout << "target pos" << endl;
			//cout << targetPos.x << " " << targetPos.y << " " << targetPos.z << endl;

			if (chunks[ivec3_hash(getChunkFromPos(targetPos))]->getBlock(targetPos) == 0) 
			{
				continue;
			}

			return Chunk::getBlock(chunks[ivec3_hash(getChunkFromPos(targetPos))]->getBlock(targetPos));
		}

		return AirBlock::getInstance();
	}

	void breakBlock(const glm::vec3& lookAt, const glm::vec3& look) {

		glm::ivec3 targetPos;

		for (float i = 1; i <= 3.0; i += 0.25) {

			targetPos.x = lookAt.x + look.x * i;
			targetPos.y = lookAt.y + look.y * i;
			targetPos.z = lookAt.z + look.z * i;

			if (chunks[ivec3_hash(getChunkFromPos(targetPos))]->getBlock(targetPos) == 0)
			{
				continue;
			}

			chunks[ivec3_hash(getChunkFromPos(targetPos))]->setBlock(targetPos, 0);
			return;
		}
	}


	void update(glm::vec3 pos) {
		if (pos != playerPos) {
			playerPos = pos;

			if (getChunkFromPos()) {
				pruneChunks();
			}
		}
	}

	/*
	void addPlayer(Player* player) {
		players[player.getName()] = player;
	}
	*/

	void render(ShaderProgram &shader) {

		for (auto chunk : chunks) {
			chunk.second->renderChunk(shader);
		}
	}

private:

	enum Direction {
		NORTH,
		EAST,
		SOUTH,
		WEST,
		UP,
		DOWN
	};

	unordered_map<int, Chunk*> chunks;

	//unordered_map<string, Player*> players;
	glm::vec3 playerPos;
	glm::ivec3 chunkPos;

	const unsigned short renderDistance = 1;

	Direction moving;

	World()
		:playerPos(0, 0, 0), chunkPos(0, 0, 0)
	{
		//players["TestPlayer"] = new Player()
		generateSurrounding();
		//chunks[ivec3_hash(glm::ivec3(0, -16, 0))] = new Chunk(glm::ivec3(0, -16, 0));
		//generateSurrounding(-16);
	}

	/*
	void generateChunk() {
		chunks[ivec3_hash(chunkPos)] = new Chunk(chunkPos);
		std::cout << chunkPos.x << " " << chunkPos.y << " " << chunkPos.z << " = " << ivec3_hash(chunkPos) << std::endl;

		for (auto chunk : chunks)
			std::cout << chunk.first << endl;

		cout << "================================================" << endl;
	}
	*/

	bool getChunkFromPos() {

		int temp = playerPos.x / 16;
		if (playerPos.x < 0)
			temp--;
		temp *= 16;
		if (temp != chunkPos.x) {
			if (temp > chunkPos.x)
				moving = Direction::NORTH;
			else
				moving = Direction::SOUTH;
			chunkPos.x = temp;
			return true;
		}

		temp = playerPos.y / 16;
		if (playerPos.y < 0)
			temp--;
		temp *= 16;
		if (temp != chunkPos.y) {
			if (temp > chunkPos.y)
				moving = Direction::UP;
			else
				moving = Direction::DOWN;
			chunkPos.y = temp;
			return true;
		}

		temp = playerPos.z / 16;
		if (playerPos.z < 0)
			temp--;
		temp *= 16;
		if (temp != chunkPos.z) {
			if (temp > chunkPos.z)
				moving = Direction::EAST;
			else
				moving = Direction::WEST;
			chunkPos.z = temp;
			return true;
		}

		return false;
	}

	void pruneChunks() {
		switch (moving) {
		case NORTH:
			for (short i = renderDistance * -1; i <= renderDistance; i++) {

				/*
				cout << "Erasing..." << endl;
				cout << chunkPos.x - 16 * (renderDistance + 1) << " " << 0 << " " << i * 16 + chunkPos.z << " = " <<
					ivec3_hash(glm::ivec3(glm::ivec3(chunkPos.x - 16 * (renderDistance + 1), 0, i * 16 + chunkPos.z))) << endl;
				*/

				//erase chunks past render distance
				chunks.erase(ivec3_hash(glm::ivec3(chunkPos.x - 16 * (renderDistance + 1), 0, i * 16 + chunkPos.z)));

				/*
				cout << "Adding..." << endl;
				cout << chunkPos.x + renderDistance * 16 << " " << 0 << " " << i * 16 + chunkPos.z << " = " <<
					ivec3_hash(glm::ivec3(chunkPos.x + renderDistance * 16, 0, i * 16 + chunkPos.z)) << endl;
				*/

				//add chunks at render distance
				chunks[ivec3_hash(glm::ivec3(chunkPos.x + renderDistance * 16, 0, i * 16 + chunkPos.z))]
					= new Chunk(glm::ivec3(chunkPos.x + renderDistance * 16, 0, i * 16 + chunkPos.z));
			}
			//cout << "================================================" << endl;
			return;

		case EAST:
			for (short i = renderDistance * -1; i <= renderDistance; i++) {

				//erase chunks past render distance
				chunks.erase(ivec3_hash(glm::ivec3(i * 16 + chunkPos.x, 0, chunkPos.z - 16 * (renderDistance + 1))));

				//add chunks at render distance
				chunks[ivec3_hash(glm::ivec3(i * 16 + chunkPos.x, 0, chunkPos.z + renderDistance * 16))]
					= new Chunk(glm::ivec3(i * 16 + chunkPos.x, 0, chunkPos.z + renderDistance * 16));
			}
			return;

		case SOUTH:
			for (short i = renderDistance * -1; i <= renderDistance; i++) {

				//erase chunks past render distance
				chunks.erase(ivec3_hash(glm::ivec3(chunkPos.x + 16 * (renderDistance + 1), 0, i * 16 + chunkPos.z)));

				//add chunks at render distance
				chunks[ivec3_hash(glm::ivec3(chunkPos.x - renderDistance * 16, 0, i * 16 + chunkPos.z))]
					= new Chunk(glm::ivec3(chunkPos.x - renderDistance * 16, 0, i * 16 + chunkPos.z));
			}
			return;

		case WEST:
			for (short i = renderDistance * -1; i <= renderDistance; i++) {

				//erase chunks past render distance
				chunks.erase(ivec3_hash(glm::ivec3(i * 16 + chunkPos.x, 0, chunkPos.z + 16 * (renderDistance + 1))));

				//add chunks at render distance
				chunks[ivec3_hash(glm::ivec3(i * 16 + chunkPos.x, 0, chunkPos.z - renderDistance * 16))]
					= new Chunk(glm::ivec3(i * 16 + chunkPos.x, 0, chunkPos.z - renderDistance * 16));
			}
			return;
		}
	}

	void generateSurrounding(int level = 0) {
		for (short i = renderDistance * -1; i <= renderDistance; i++) {
			for (short j = renderDistance * -1; j <= renderDistance; j++) {
				chunks[ivec3_hash(glm::ivec3(i * 16 + chunkPos.x, level, j * 16 + chunkPos.z))]
					  = new Chunk(glm::ivec3(i * 16 + chunkPos.x, level, j * 16 + chunkPos.z));
			}
		}
	}

	int ivec3_hash(glm::ivec3 pos) {
		return pos.x * 1013 + pos.y * 907 + pos.z * 809;
	}
};