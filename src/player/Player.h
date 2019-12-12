#pragma once

#include <time.h>
#include <string>

#include <world/World.h>

class Player {
public:
	//Player() {}

	Player(string name, FPSCamera* cam, bool creative, int winHeight, int winWidth, GLFWwindow* window, unsigned short renderDistance = 1)
		:name(name), cam(cam), renderDistance(renderDistance), creativeMode(creative), winHeight(winHeight), winWidth(winWidth), window(window), sensitivity(0.25f),
		camPos(cam->getPos()), jumpTime(clock() / (CLOCKS_PER_SEC / 1000)), isJumping(false)
	{
		//this->world = world;
		//world = World::getInstance();
	}

	/*
	glm::vec3 getPos() {
		return cam->getPos();
	}
	*/

	void updatePos(glm::vec3 camPos) {
		this->camPos = camPos;
	}

	glm::vec3 getPos() {
		return pos;
	}

	glm::vec3 getCamPos() {
		return camPos;
	}

	string getName() {
		return name;
	}

	const glm::vec3& getLook() {
		return cam->getLook();
	}

	const glm::vec3& getLookAt() {
		return cam->getTargetPos();
	}

	unsigned short& getRenderDistance() {
		return renderDistance;
	}

	void setCreative(bool creative) {
		creativeMode = creative;
	}
	
	bool update(double elapsedTime) {

		camPos = cam->getPos();
		pos = camPos;
		pos.y -= 2.25f;
		look = cam->getLook();
		move = cam->getLook();
		move.y = 0;

		glfwGetCursorPos(window, &mouseX, &mouseY);
		cam->rotate((float)(winWidth / 2.0 - mouseX) * sensitivity, (float)(winHeight / 2.0 - mouseY) * sensitivity);
		glfwSetCursorPos(window, winWidth / 2.0, winHeight / 2.0);


		if (creativeMode) {
			move_speed = 10;
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
				cam->move(move_speed * (float)elapsedTime * glm::vec3(0, 1, 0));
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				cam->move(move_speed * (float)elapsedTime * glm::vec3(0, -1, 0));
		}
		else {
			//if ()



			if (!isJumping) {
				if (jumpTime + 175 <= clock() / (CLOCKS_PER_SEC / 1000) && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
					cam->move(glm::vec3(0, 1, 0));
					isJumping = true;
					jumpTime = clock() / (CLOCKS_PER_SEC / 1000);
				}
			}
			else {
				if (jumpTime + 175 <= clock() / (CLOCKS_PER_SEC / 1000)) {
					cam->move(glm::vec3(0, -1, 0));
					isJumping = false;
					jumpTime = clock() / (CLOCKS_PER_SEC / 1000);
				}
			}
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
			move_speed = 15;
		else
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			move_speed = 5;
		else
			move_speed = 10;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cam->move(move_speed * (float)elapsedTime * move);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cam->move(move_speed * (float)elapsedTime * -move);

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cam->move(move_speed * (float)elapsedTime * -cam->getRight());
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cam->move(move_speed * (float)elapsedTime * cam->getRight());

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			return true;
			//world->breakBlock(name, getLookAt(), getLook());

		return false;
	}
	//subcriber pattern / command and observer
	//on click event



private:

	std::string name;

	//World* world = World::getInstance();
	FPSCamera* cam;
	GLFWwindow* window;

	glm::vec3 pos;
	glm::vec3 camPos;
	glm::vec3 look;
	glm::vec3 move;

	unsigned char inventory[36] = { 0 };
	unsigned char holding = 0;

	bool creativeMode;
	unsigned short renderDistance;
	float sensitivity;
	int winHeight, winWidth;
	double mouseX, mouseY;
	bool isJumping;
	clock_t jumpTime;
	int move_speed = 10;
};