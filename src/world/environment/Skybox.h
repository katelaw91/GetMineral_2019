/*
#pragma once

static const GLfloat skybox_vertices[] = {
	//position X, Y, Z     //texture coords

	// front face
	 100.0f, -100.0f,  100.0f,	
	-100.0f,  100.0f,  100.0f,	
	 100.0f,  100.0f,  100.0f,	
	-100.0f, -100.0f,  100.0f,	
	-100.0f,  100.0f,  100.0f,	
	 100.0f, -100.0f,  100.0f,	

	 // back face
	  100.0f,  100.0f, -100.0f,	
	 -100.0f,  100.0f, -100.0f,	
	  100.0f, -100.0f, -100.0f,	
	 -100.0f,  100.0f, -100.0f,	
	 -100.0f, -100.0f, -100.0f,	
	  100.0f, -100.0f, -100.0f,	

	  // left face
	  -100.0f, -100.0f,  100.0f,	
	  -100.0f,  100.0f, -100.0f,	
	  -100.0f,  100.0f,  100.0f,	
	  -100.0f, -100.0f, -100.0f,	
	  -100.0f,  100.0f, -100.0f,	
	  -100.0f, -100.0f,  100.0f,	

	  // right face
	   100.0f, -100.0f, -100.0f,	
	   100.0f,  100.0f,  100.0f,	
	   100.0f,  100.0f, -100.0f,	
	   100.0f, -100.0f,  100.0f,	
	   100.0f,  100.0f,  100.0f,	
	   100.0f, -100.0f, -100.0f,	

	   // top face
		100.0f,  100.0f,  100.0f,	
	   -100.0f,  100.0f, -100.0f,	
		100.0f,  100.0f, -100.0f,	
	   -100.0f,  100.0f,  100.0f, 
	   -100.0f,  100.0f, -100.0f, 
		100.0f,  100.0f,  100.0f, 

		// bottom face
		 100.0f, -100.0f, -100.0f,
		-100.0f, -100.0f,  100.0f,
		 100.0f, -100.0f,  100.0f,
		-100.0f, -100.0f, -100.0f,
		-100.0f, -100.0f,  100.0f,
		 100.0f, -100.0f, -100.0f,
};
*/

class Skybox {
public:

	static Skybox* getInstance() {
		static Skybox* instance = new Skybox();
		return instance;
	}

	/*
	static const GLfloat* const getVertices() {
		return skybox_vertices;
	}

	static const unsigned int getSize() {
		return sizeof(skybox_vertices);
	}
	*/

	void bindTexture() {
		texture->bind();
	}

	/*
	void bindShader() {
		shader->use();
	}

	ShaderProgram* getShader() {
		return shader;
	}

	void render(const FPSCamera &fpsCam) {
		glm::mat4 pvm;
		pvm = glm::perspective(glm::radians(fpsCam.getFOV()), 1920.0f / 1080, 0.1f, 100.0f);
		pvm *= glm::mat4(glm::mat3(fpsCam.getViewMatrix()));
		shader->setUniform("pvm", pvm);
		shader->setUniform("model", glm::translate(glm::mat4(1), glm::vec3(0, 0, 0)));

		texture->bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	*/
	
private:

	Skybox() {
		//shader->loadShaders("src/util/shaders/skybox.vert", "src/util/shaders/cube.frag");
	}

	//ShaderProgram* shader;

	Texture2D* texture = new Texture2D( "res/textures/skybox_front.png",
										"res/textures/skybox_back.png",
										"res/textures/skybox_right.png",
										"res/textures/skybox_left.png",
										"res/textures/skybox_top.png",
										"res/textures/skybox_bottom.png");
};