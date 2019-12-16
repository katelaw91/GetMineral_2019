#include "Block.h"

class LeafBlock : public Block {
public:

	static LeafBlock* getInstance() {
		static LeafBlock* instance = new LeafBlock();
		return instance;
	}

	void bindTexture() {
		texture->bind();
	}

	unsigned char getIdFromBlock() {
		return 4;
	}

private:

	LeafBlock() {}

	Texture3D* texture = new Texture3D("res/textures/leaf.png");
};