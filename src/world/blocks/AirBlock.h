#include "Block.h"

class AirBlock : public Block {
public:

	static AirBlock* getInstance() {
		static AirBlock* instance = new AirBlock();
		return instance;
	}

	void bindTexture() {}

	unsigned char getIdFromBlock() {
		return 0;
	}

private:

	AirBlock() {}
};