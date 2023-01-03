#pragma once
#include <windows.h>
#include <gl/GL.h>
#include "vector3f.h"


class Camera
{
protected:
	void RotateView(float angle, float x, float y, float z);
public:
	Camera();
	Vector3f mPos, mViewCenter, mUp;
	bool mbMoveLeft, mbMoveRight, mbMoveForward, mbMoveBack;
	void Pitch(float angle);
	void Yaw(float angle);
	void Update(float deltaTime);
};
