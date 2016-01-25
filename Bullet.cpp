#include "Bullet.h"

Bullet::Bullet(const SF3dVector& position, const SF3dVector&  velocity, GLfloat width, GLfloat height, GLfloat depth, unsigned damage, bool hostile) :
					color(Color(0.1, 0, 0)),Movable(position, velocity, width, height, depth),
					damage(damage), hostile(hostile) {
}

Bullet::~Bullet() {
}

void Bullet::update() {
	static const GLfloat colorStep = 0.1;
	static const GLfloat update = 0.5;

	position.x += update * velocity.x;
	position.y += update * velocity.y;
	position.z += update * velocity.z;

	// teNcza
	if (color.b == 0 && color.r > 0.0){
		color.r += colorStep;
		if (color.r > 1.0) {
			color.r = 1.0;
			color.g += colorStep;
			if (color.g > 1.0) {
				color.g = 1.0;
				color.r = 0.0;
			}
		}
	}
	else if (color.r == 0 && color.g > 0.0) {
		color.g += colorStep;
		if (color.g > 1.0) {
			color.g = 1.0;
			color.b += colorStep;
			if (color.b > 1.0) {
				color.b = 1.0;
				color.g = 0.0;
			}
		}
	}
	else if (color.g == 0 && color.b > 0.0) {
		color.b += colorStep;
		if (color.b > 1.0) {
			color.b = 1.0;
			color.r += colorStep;
			if (color.r > 1.0) {
				color.r = 1.0;
				color.b = 0.0;
			}
		}
	}
}

void Bullet::display() {
	GLfloat x = position.x;
	GLfloat y = position.y;
	GLfloat z = position.z;

	glPushMatrix();
		glColor3d(color.r, color.g, color.b);

		glBegin(GL_LINES);
			glVertex3f(x - width / 2, y - height / 2, z - depth);
			glVertex3f(x - width / 2, y + height / 2, z - depth);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(x + width / 2, y + height / 2, z - depth);
			glVertex3f(x + width / 2, y - height / 2, z - depth);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(x - width / 2, y - height / 2, z - depth);
			glVertex3f(x - width / 2, y - height / 2, z);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(x - width / 2, y + height / 2, z - depth);
			glVertex3f(x - width / 2, y + height / 2, z);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(x + width / 2, y + height / 2, z - depth);
			glVertex3f(x + width / 2, y + height / 2, z);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(x + width / 2, y - height / 2, z - depth);
			glVertex3f(x + width / 2, y - height / 2, z);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(x - width / 2, y - height / 2, z);
			glVertex3f(x - width / 2, y + height / 2, z);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(x + width / 2, y + height / 2, z);
			glVertex3f(x + width / 2, y - height / 2, z);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(x + width / 2, y + height / 2, z);
			glVertex3f(x - width / 2, y + height / 2, z);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(x + width / 2, y - height / 2, z);
			glVertex3f(x - width / 2, y - height / 2, z);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(x + width / 2, y + height / 2, z - depth);
			glVertex3f(x - width / 2, y + height / 2, z - depth);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(x + width / 2, y - height / 2, z - depth);
			glVertex3f(x - width / 2, y - height / 2, z - depth);
		glEnd();

	glPopMatrix();
}

GLfloat Bullet::getPosZ() const {
	return position.z;
}

unsigned Bullet::getDamage() const {
	return damage;
}

bool Bullet::isHostile() const {
	return hostile;
}