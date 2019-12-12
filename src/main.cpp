#define GLEW_STATIC

#include <iostream>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"

#include "util/shaders/shaderProgram.h"
#include "util/camera/camera.h"

#include "world/blocks/Block.h"
#include "world/World.h"
#include "world/environment/Skybox.h"
#include "player/Player.h"

const char* APP_TITLE = "Get Mineral";
int gWinWidth = 1920;// 1024;
int gWinHeight = 1080;// 768;
GLFWwindow* pWindow = NULL; 
bool gFullScreen = false;
bool gWireFrame = false;

const double ZOOM_SENSITIVITY = -3.0;
float MOVE_SPEED = 15.0;
const float MOUSE_SENSITIVITY = 0.25f;
const int CHUNK_SIZE = 16;

//World* world = World::getInstance();
FPSCamera fpsCam(glm::vec3(0.0f, 2.25f, 5.0f));
World* world = World::getInstance();


void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_onFrameBufferSiz(GLFWwindow *window, int width, int height);
void showFPS(GLFWwindow* window);
bool initOpenGL();

using namespace std;

int main()
{
	if (!initOpenGL())
	{
		cerr << "GLFW initialization failed." << endl;
		return -1;
	}

	//world->addPlayer("TestPlayer", &fpsCam, gWinWidth, gWinHeight, pWindow);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, Block::getSize(), Block::getVertices(), GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	glEnableVertexAttribArray(0);

	ShaderProgram shader;
	shader.loadShaders("src/util/shaders/cube.vert", "src/util/shaders/cube.frag");

	ShaderProgram skybox;
	skybox.loadShaders("src/util/shaders/skybox.vert", "src/util/shaders/cube.frag");

	//Texture2D cursor;
	//cursor.loadTexture("res/textures/cursor.png");

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glDepthMask(GL_FALSE);
	glDepthMask(GL_TRUE);


	Player* player = new Player("TestPlayer", &fpsCam, true, gWinWidth, gWinHeight, pWindow);
	world->addPlayer(player);
	//player->setCreative(true);


	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(pWindow))
	{
		showFPS(pWindow);
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::mat4 pvm;




		//player->update(deltaTime);

		//cout << player->getPos().x << " " << player->getPos().y << " " << player->getPos().z << endl;
		//cout << (int)world->getBlock(player->getLookAt(), player->getLook())->getIdFromBlock() << endl;

		/*
		glm::vec3 look = player->getLookAt();
		glm::ivec3 i_look = look;
		float dist = glm::distance(player->getPos(), player->getLookAt());
		float length = 1.5;
	

		cout << player->getPos().x << " " << player->getPos().y << " " << player->getPos().z << endl;
		cout << look.x << " " << look.y << " " << look.z << endl;
		cout << i_look.x << " " << i_look.y << " " << i_look.z << endl;

		glm::vec3 newLength(look.x * (length / dist), look.y * (length / dist), look.z * (length / dist));
		glm::ivec3 i_newLength = newLength;

		cout << newLength.x << " " << newLength.y << " " << newLength.z << endl;
		cout << i_newLength.x << " " << i_newLength.y << " " << i_newLength.z << endl;
		*/

		/*
		look.x %= 16;
		look.y %= 16;
		look.z %= 16;
		cout << (look.x < 0 ? look.x * -1 : look.x) << " " <<
				(look.y < 0 ? look.y * -1 : look.y) << " " <<
				(look.z < 0 ? look.z * -1 : look.z) << endl;
		*/

		
		//cout << player->getPos().x << " " << player->getPos().y << " " << player->getPos().z << endl;
		//cout << look.x << " " << look.y << " " << look.z << endl;
		//look -= player->getPos();
		//cout << look.x - player->getPos().x << " " << look.y  - player->getPos().y << " " << look.z - player->getPos().z << endl;

		//cout << glm::distance(glm::vec3(look), player->getPos()) << endl;

		//cout << "======================================" << endl;
		//cout << (int)world->getBlock(player->getLookAt())->getIdFromBlock() << endl;


		world->update(player->getName(), deltaTime);
		
		//skybox
		skybox.use();
		pvm = glm::perspective(glm::radians(fpsCam.getFOV()), (float)gWinWidth / (float)gWinHeight, 0.1f, 100.0f);
		pvm *= glm::mat4(glm::mat3(fpsCam.getViewMatrix()));
		skybox.setUniform("pvm", pvm);
		skybox.setUniform("model", glm::translate(glm::mat4(1), glm::vec3(0, 0, 0)));
		Skybox::getInstance()->bindTexture();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//chunks
		shader.use();
		pvm = glm::perspective(glm::radians(fpsCam.getFOV()), (float)gWinWidth / (float)gWinHeight, 0.1f, 100.0f);
		pvm *= fpsCam.getViewMatrix();
		shader.setUniform("pvm", pvm);

		world->render(player->getName(), shader);


		/*
		cursor.bind();
		pvm = glm::perspective(glm::radians(fpsCam.getFOV()), (float)gWinWidth / (float)gWinHeight, 0.1f, 100.0f);
		pvm *= glm::mat4(glm::mat3(fpsCam.getViewMatrix()));
		shader.setUniform("pvm", pvm);
		shader.setUniform("model", glm::translate(glm::mat4(1), glm::vec3(0, 0, 0)));

		//model = glm::translate(model, floorPos) * glm::scale(model, glm::vec3(10.0f, 0.01f, 10.0f));

		//shaderProgram.setUniform("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		*/


		glfwSwapBuffers(pWindow);

		lastTime = currentTime;
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glfwTerminate();
	return 0;
}

void glfw_onFrameBufferSiz(GLFWwindow* window, int width, int height)
{
	gWinWidth = width;
	gWinHeight = height;
	glViewport(0, 0, gWinWidth, gWinHeight);
}

bool initOpenGL() {
	//initialize GLFW
	if (!glfwInit())
	{
		cerr << "GLFW initialization failed" << endl;
		return false;
	}

	//set version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//set modern opengl
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//set compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if (gFullScreen)
	{
		GLFWmonitor* pMonitor = glfwGetPrimaryMonitor(); //get pointer to primary monitor
		const GLFWvidmode* pVmode = glfwGetVideoMode(pMonitor);
		if (pVmode != NULL)
		{
			pWindow = glfwCreateWindow(pVmode->width, pVmode->height, APP_TITLE, pMonitor, NULL);
		}
	}
	else {
		pWindow = glfwCreateWindow(gWinWidth, gWinHeight, APP_TITLE, NULL, NULL);
	}

	if (pWindow == NULL)
	{
		cerr << "Failed to create GLFW Window" << endl;
		glfwTerminate();
		return false;
	}

	//if window creation successful, make current window
	glfwMakeContextCurrent(pWindow);
	glfwSetKeyCallback(pWindow, glfw_onKey);
	//glfwSetCursorPosCallback(pWindow, glfw_onMouseMove);
	//glfwSetScrollCallback(TODO scroll inventory);

	//Hides and grabs cursor, unlimited movement
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(pWindow, gWinWidth / 2.0, gWinHeight / 2.0);

	//initialize GLEW on window creation
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW initialization failed." << endl;
		return false;
	}

	//set screen color
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f); //RGBAlpha color channels, from 0 to 1
	glViewport(0, 0, gWinWidth, gWinHeight);

	return true;
}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//exit on esc
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		//gWireFrame = !gWireFrame;
		if (gWireFrame = !gWireFrame)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void showFPS(GLFWwindow* window)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime(); //returns number of seconds since GLFW started as double

	elapsedSeconds = currentSeconds - previousSeconds;

	//limit text update 4 times per second
	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		ostringstream outs;
		outs.precision(3);
		outs << fixed
			<< APP_TITLE << "  "
			<< "FPS: " << fps << "  "
			<< "Frame Time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outs.str().c_str());

		frameCount = 0; //reset
	}
	frameCount++; //tick frames
}