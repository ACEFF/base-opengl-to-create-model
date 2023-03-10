#include "camera.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "vector3f.h"
#include <stdio.h>

Camera::Camera() :mPos(0.0f, 0.0f, 0.0f), mViewCenter(0.0f, 0.0f, -1.0f),
mUp(0.0f, 1.0f, 0.0f), mbMoveLeft(false), mbMoveRight(false), mbMoveForward(false), mbMoveBack(false)
{

}

void Camera::RotateView(float angle, float x, float y, float z)
{
	Vector3f viewDirection = mViewCenter - mPos;
	Vector3f newDirection;
	float C = cosf(angle);
	float S = sinf(angle);

	Vector3f tempX(C + x * x * (1 - C), x * y * (1 - C) - z * S, x * z * (1 - C) + y * S);
	newDirection.x = tempX * viewDirection;

	Vector3f tempY(x * y * (1 - C) + z * S, C + y * y * (1 - C), y * z * (1 - C) + x * S);
	newDirection.y = tempY * viewDirection;

	Vector3f tempZ(x * z * (1 - C) - y * S, y * z * (1 - C) + x * S, C + z * z * (1 - C));
	newDirection.z = tempZ * viewDirection;

	mViewCenter = mPos + newDirection;
}

void Camera::Pitch(float angle)
{
	Vector3f viewDirection = mViewCenter - mPos;
	viewDirection.Normalize();
	Vector3f rightDirection = viewDirection ^ mUp;
	rightDirection.Normalize();
	RotateView(angle, rightDirection.x, rightDirection.y, rightDirection.z);
}

void Camera::Yaw(float angle)
{
	RotateView(angle, mUp.x, mUp.y, mUp.z);
}

void Camera::Update(float deltaTime)
{
	//update everything
	float moveSpeed = 5.0f;

	float rotateSpeed = 1.0f;
	if (mbMoveLeft)
	{
		Vector3f viewDirection = mViewCenter - mPos;
		viewDirection.Normalize();
		Vector3f rightDirection = viewDirection ^ mUp;
		rightDirection.Normalize();
		mPos = mPos + rightDirection * moveSpeed * deltaTime * -1.0f;
		mViewCenter = mViewCenter + rightDirection * moveSpeed * deltaTime * -1.0f;
	}
	if (mbMoveRight)
	{
		Vector3f viewDirection = mViewCenter - mPos;
		viewDirection.Normalize();
		Vector3f rightDirection = viewDirection ^ mUp;
		rightDirection.Normalize();
		mPos = mPos + rightDirection * moveSpeed * deltaTime;
		mViewCenter = mViewCenter + rightDirection * moveSpeed * deltaTime;
	}
	if (mbMoveForward)
	{
		Vector3f forwardDirection = mViewCenter - mPos;
		forwardDirection.Normalize();
		mPos = mPos + forwardDirection * moveSpeed * deltaTime;
		mViewCenter = mViewCenter + forwardDirection * moveSpeed * deltaTime;
	}
	if (mbMoveBack)
	{
		Vector3f backDirection = mPos - mViewCenter;
		backDirection.Normalize();
		mPos = mPos + backDirection * moveSpeed * deltaTime;
		mViewCenter = mViewCenter + backDirection * moveSpeed * deltaTime;
	}
	//set model veiw matrix

	gluLookAt(mPos.x, mPos.y, mPos.z,
		mViewCenter.x, mViewCenter.y, mViewCenter.z,
		mUp.x, mUp.y, mUp.z);
}