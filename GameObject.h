#pragma once

#include "glut.h"
#include "Camera.h"

class GameObject {
protected:
	const GLfloat width;
	const GLfloat height;
	const GLfloat depth;
	SF3dVector position;
	SF3dVector velocity;

public:
	GameObject(GLfloat width, GLfloat height, GLfloat depth);

	~GameObject();

	void update();

	void display();
};

