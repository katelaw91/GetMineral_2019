#include "Block.h"

class DirtBlock : public Block {
public:

	static DirtBlock* getInstance() {
		static DirtBlock* instance = new DirtBlock();
		return instance;
	}

	void bindTexture() {
		texture->bind();
	}

	unsigned char getIdFromBlock() {
		return 2;
	}

private:

	DirtBlock() {}

	Texture3D* texture = new Texture3D("res/textures/dirt.png");
};