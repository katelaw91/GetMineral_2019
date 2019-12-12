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

	Texture3D* texture = new Texture3D( "res/textures/grass_side.png",
										"res/textures/grass_top_new.png",
										"res/textures/dirt.png");
};