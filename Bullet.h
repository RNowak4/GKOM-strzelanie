#pragma once

#include "glut.h"
#include "Color.h"
#include "Movable.h"

class Bullet : public Movable {
private:
	bool hostile;
	Color color;
	unsigned damage;

public:
	Bullet(const SF3dVector& position, const SF3dVector& velocit, GLfloat width, GLfloat height, GLfloat depth, unsigned damage, bool hostile);
	
	~Bullet();

	void update();

	void display();

	GLfloat getPosZ() const;

	unsigned getDamage() const;

	bool isHostile() const;
};