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

	Texture2D* texture = new Texture2D("res/textures/dirt.png");
};