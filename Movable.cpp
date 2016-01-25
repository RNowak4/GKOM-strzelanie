#include "Movable.h"


Movable::Movable(const SF3dVector& position, const SF3dVector& velocity, GLfloat width, GLfloat height, GLfloat depth) :
Coordinable(position, width, height, depth), velocity(velocity) {
}


Movable::~Movable() {
}

const SF3dVector& Movable::getVelocity() const {
	return velocity;
}

void Movable::setVelocity(const SF3dVector& v) {
	this->velocity = v;
}
