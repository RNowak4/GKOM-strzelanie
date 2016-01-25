#pragma once

#include "Coordinable.h"

class Movable :
	public Coordinable {
protected:
	SF3dVector velocity;

public:
	Movable(const SF3dVector& position, const SF3dVector& velocity, GLfloat width, GLfloat height, GLfloat depth);
		
	~Movable();

	const SF3dVector& getVelocity() const;

	void setVelocity(const SF3dVector& v);
};

