#pragma once

#include "Camera.h"

class Coordinable {
protected:
	const GLfloat width;
	const GLfloat height;
	const GLfloat depth;
	SF3dVector position;

public:
	Coordinable(const SF3dVector& position, GLfloat width, GLfloat height, GLfloat depth);
	
	~Coordinable();

	GLfloat getWidth() const;

	GLfloat getHeight() const;

	GLfloat getDepth() const;

	const SF3dVector& getPosition() const;
};

