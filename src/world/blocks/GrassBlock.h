#include "Block.h"

class GrassBlock : public Block {
public:

	static GrassBlock* getInstance() {
		static GrassBlock* instance = new GrassBlock();
		return instance;
	}

	void bindTexture() {
		texture->bind();
	}

	unsigned char getIdFromBlock() {
		return 1;
	}

private:

	GrassBlock() {}

	Texture2D* texture = new Texture2D( "res/textures/grass_side.png",
										"res/textures/grass_top_new.png",
										"res/textures/dirt.png");
};