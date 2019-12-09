#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp" //for pi vector


/*********ABSTRACT CAMERA CLASS *********/

class Camera
{
public:
	glm::mat4 getViewMatrix() const;
	virtual void setPosition(const glm::vec3& position) {}
	virtual void rotate(float yaw, float pitch) {} //in degrees
	virtual void move(const glm::vec3 &offsetPos) {}

	const glm::vec3& getLook() const;
	const glm::vec3& getRight() const;
	const glm::vec3& getUp() const;
	const glm::vec3& getPos() const;
	const glm::vec3& getTargetPos() const;

	const float& getFOV() const { return mFOV; }
	//void setFOV(float fov) { mFOV = fov; } //in degrees



protected:
	Camera();

	glm::vec3 mPosition;
	glm::vec3 mTargetPos;
	glm::vec3 mUp;
	glm::vec3 mLook;
	glm::vec3 mRight;
	const glm::vec3 WORLD_UP;

	//Eulers angles (in radians)
	float mYaw;
	float mPitch;

	//Camera parameters
	float mFOV; //degrees
};

#endif //CAMERA_H


/*

class OrbitCamera : public Camera
{
public:
	OrbitCamera();
	virtual void rotate(float yaw, float pitch); //in degrees
	void setLookAt(const glm::vec3 &targt);
	void setRadius(float radius);

private:
	void updateCameraVectors();
	float mRadius;
};

*/
class FPSCamera : public Camera
{
public:
	FPSCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float yaw = glm::pi<float>(), float itch = 0.0f); // (yaw) initial angle faces -Z

	virtual void setPosition(const glm::vec3 &position);
	virtual void rotate(float yaw, float pitch); //in degrees
	void setLookAt(const glm::vec3 &targt);
	virtual void move(const glm::vec3 &offsetPos);
	glm::vec3 getPos();

private:
	void updateCameraVectors();
	float mRadius;
};