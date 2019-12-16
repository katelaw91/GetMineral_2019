#include "Block.h"

class BarkBlock : public Block {
public:

	static BarkBlock* getInstance() {
		static BarkBlock* instance = new BarkBlock();
		return instance;
	}

	void bindTexture() {
		texture->bind();
	}

	unsigned char getIdFromBlock() {
		return 3;
	}

private:

	BarkBlock() {}

	Texture3D* texture = new Texture3D("res/textures/bark.png");
}; 
