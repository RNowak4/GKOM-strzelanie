#include "Coordinable.h"

Coordinable::Coordinable(const SF3dVector& position, GLfloat width, GLfloat height, GLfloat depth) : 
					position(position), width(width), height(height), depth(depth) {
}

Coordinable::~Coordinable() {
}

GLfloat Coordinable::getWidth() const {
	return width;
}

GLfloat Coordinable::getHeight() const {
	return height;
}

GLfloat Coordinable::getDepth() const {
	return depth;
}

const SF3dVector& Coordinable::getPosition() const {
	return position;
}