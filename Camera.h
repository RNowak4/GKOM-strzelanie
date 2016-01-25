#pragma once

#include "glut.h"		
#define PI 3.1415926535897932384626433832795
#define PIdiv180 (PI/180.0)

struct SF3dVector {
	GLfloat x, y, z;
};

SF3dVector F3dVector(GLfloat x, GLfloat y, GLfloat z);

class Camera {
private:

	SF3dVector ViewDir;
	SF3dVector RightVector;
	SF3dVector UpVector;
	SF3dVector Position;

	GLfloat RotatedX, RotatedY, RotatedZ;

public:
	Camera();
	void Render(void);	

	void Move(SF3dVector Direction);
	void RotateX(GLfloat Angle);
	void RotateY(GLfloat Angle);
	void RotateZ(GLfloat Angle);

	void MoveForward(GLfloat Distance);
	void MoveUpward(GLfloat Distance);
	void StrafeRight(GLfloat Distance);

	void setPosition(const SF3dVector& position);
};


