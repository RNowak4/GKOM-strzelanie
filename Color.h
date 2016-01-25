#pragma once

#include "glut.h"

struct Color {
	GLdouble r;
	GLdouble g;
	GLdouble b;

	Color(GLdouble r, GLdouble g, GLdouble b);
	~Color();
};

