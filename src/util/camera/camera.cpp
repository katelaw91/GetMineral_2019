#include "camera.h"
#include "glm/gtx/transform.hpp"

//default camera values
const float DEF_FOV = 80;// 45.0f;

/********* BASE/VIRTUAL CAM *********/
Camera::Camera()
	:mPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
	mTargetPos(glm::vec3(1.0f, 2.0f, 0.0f)),
	mUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	mRight(0.0f, 0.0f, 1.0f),
	WORLD_UP(0.0f, 1.0f, 0.0f),
	mYaw(0.0f),
	mPitch(0.0f),
	mFOV(DEF_FOV)
{
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(mPosition, mTargetPos, mUp);
}

const glm::vec3& Camera::getLook() const
{
	return mLook;
}

const glm::vec3& Camera::getRight() const
{
	return mRight;
}

const glm::vec3& Camera::getUp() const
{
	return mUp;
}

const glm::vec3& Camera::getPos() const {
	return mPosition;
}

const glm::vec3& Camera::getTargetPos() const {
	return mTargetPos;
}

/********* FPS CAM *********/
FPSCamera::FPSCamera(glm::vec3 position, float yaw, float pitch)
{
	mPosition = position;
	mYaw = yaw;
	mPitch = pitch;
}

//Sets the camera position in world space
void FPSCamera::setPosition(const glm::vec3& position)
{
	mPosition = position;
}

//Sets the incremental position of the camera in world space
void FPSCamera::move(const glm::vec3& offsetPos)
{
	mPosition += offsetPos;
	updateCameraVectors();
}

//Sets the incremental orientation of the camera
void FPSCamera::rotate(float yaw, float pitch)
{
	mYaw += glm::radians(yaw);
	mPitch += glm::radians(pitch);

	// Constrain the pitch
	mPitch = glm::clamp(mPitch, -glm::pi<float>() / 2.0f + 0.1f, glm::pi<float>() / 2.0f - 0.1f);
	updateCameraVectors();
}

//Calculates the front vector from the Camera's Euler Angles
void FPSCamera::updateCameraVectors()
{
	// Spherical to Cartesian coordinates
	// https://en.wikipedia.org/wiki/Spherical_coordinate_system (NOTE: Our coordinate sys has Y up not Z)

	// Calculate the view direction vector based on yaw and pitch angles (roll not considered)
	// radius is 1 for normalized length
	glm::vec3 look;
	look.x = cosf(mPitch) * sinf(mYaw);
	look.y = sinf(mPitch);
	look.z = cosf(mPitch) * cosf(mYaw);

	mLook = glm::normalize(look);

	// Re-calculate the Right and Up vector.  For simplicity the Right vector will
	// be assumed horizontal w.r.t. the world's Up vector.
	mRight = glm::normalize(glm::cross(mLook, WORLD_UP));
	mUp = glm::normalize(glm::cross(mRight, mLook));

	mTargetPos = mPosition + mLook;
}

glm::vec3 FPSCamera::getPos() {
	return mPosition;
}






/*

OrbitCamera::OrbitCamera()
	:mRadius(10.0f)
{

}

//Sets the target to look at
void OrbitCamera::setLookAt(const glm::vec3 &target)
{
	mTargetPos = target;
}

//Sets the radius of camera to target distance
void OrbitCamera::setRadius(float radius)
{
	mRadius = glm::clamp(radius, 2.0f, 80.0f);

}

//Rotates the camera around the target look
void OrbitCamera::rotate(float yaw, float pitch)
{
	mYaw = glm::radians(yaw);
	mPitch = glm::radians(pitch);
	mPitch = glm::clamp(mPitch, -glm::pi<float>() / 2.0f + 0.1f, glm::pi<float>() / 2.0f - 0.1f);

	updateCameraVectors();
}

//Calculates the front vector from the Camera's Euler Angles
void OrbitCamera::updateCameraVectors()
{
	//Spherical to cartesian coordinates
	mPosition.x = mTargetPos.x + mRadius * cosf(mPitch) * sinf(mYaw);
	mPosition.y = mTargetPos.y + mRadius * sinf(mPitch);
	mPosition.z = mTargetPos.z + mRadius * cosf(mPitch) * cosf(mYaw);

}
*/






