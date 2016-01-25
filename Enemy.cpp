#include "Enemy.h"
#include "Game.h"

const clock_t Enemy::timeBetweenShot = 2000;
const GLfloat Enemy::defaultEnemyWidth = 0.05;
const GLfloat Enemy::defaultEnemyHeight = 0.01;
const GLfloat Enemy::defaultEnemyDepth = 0.5;
const SF3dVector Enemy::defaultBulletVelocity = F3dVector(0, 0, 0.666);

Enemy::Enemy(Game* game, const SF3dVector& position, const SF3dVector& velocity, const Color& color, unsigned health) :
Movable(position, velocity, defaultEnemyWidth, defaultEnemyHeight, defaultEnemyDepth), 
color(color), Alive(health), lastShot(0), game(game) {
	int a = 2;
}

Enemy::~Enemy() {
}

void Enemy::display() {
	GLfloat x = position.x;
	GLfloat y = position.y;
	GLfloat z = position.z;
	
	glPushMatrix();	
		glColor3f(1, 0, 0); // red

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

void Enemy::update() {
	position.z += velocity.z;

	clock_t currentTime = clock();
	if ((currentTime - lastShot) > timeBetweenShot) {
		lastShot = currentTime;
		game->createBullet(position, defaultBulletVelocity, true);
	}
}
