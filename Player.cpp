#include "Player.h"
#include "Game.h"

const clock_t Player::timeBetweenBasicShot = 500;
const clock_t Player::timeBetweenFastShot = 30;
const GLfloat Player::defaultPlayerWidth = 0.05;
const GLfloat Player::defaultPlayerHeight = 0.01;
const GLfloat Player::defaultPlayerDepth = 0.5;
const GLfloat Player::moveStep = 0.01;
const SF3dVector Player::defaultBulletVelocity = F3dVector(0, 0, -0.666);

Player::Player(const SF3dVector& position, Game* game, unsigned health) :
Movable(position, F3dVector(0, 0, 0), defaultPlayerWidth, defaultPlayerHeight, defaultPlayerDepth),
game(game), Alive(health), lastShot(0), weapon(BASIC) {
	camera = new Camera();
	camera->Move(F3dVector(0.0, 0.03, 0.8));
}

Player::~Player() {
}

bool Player::canShoot(const clock_t currentTime) const {
	if (weapon == BASIC)
		return (currentTime - lastShot) > timeBetweenBasicShot;
	else
		return (currentTime - lastShot) > timeBetweenFastShot;
}

void Player::shoot() {
	clock_t currentTime = clock();
	if (canShoot(currentTime)) {
		lastShot = currentTime;

		if (weapon == BASIC)
			game->createBullet(position, defaultBulletVelocity, 0.01, 0.01, 0.01, 50, false);
		else 
			game->createBullet(position, defaultBulletVelocity, 0.005, 0.005, 0.005, 15, false);
	}
}

void Player::update() {
}

void Player::display() {
	camera->Render();
	drawPlayer();
}

void Player::moveLeft() {
	GLfloat newXPos = position.x - moveStep;
	GLfloat oldX = position.x;
	if (game->getLeftBorder() >= newXPos)
		position.x = game->getLeftBorder();
	else
		position.x = newXPos;

	camera->Move(F3dVector(position.x - oldX, 0.0, 0.0));
}

void Player::moveRight() {
	GLfloat oldX = position.x;
	GLfloat newXPos = position.x + moveStep;
	if (game->getRightBorder() <= newXPos)
		position.x = game->getRightBorder();
	else
		position.x = newXPos;

	camera->Move(F3dVector(position.x - oldX, 0.0, 0.0));
}

void Player::moveForward() {
	GLfloat oldZ = position.z;
	GLfloat newZPos = position.z - moveStep * 20;
	if (-game->getDepth() / 3 > newZPos)
		position.z = -game->getDepth() / 3;
	else
		position.z = newZPos;

	camera->Move(F3dVector(0.0, 0.0, position.z - oldZ));
}

void Player::moveBackward() {
	GLfloat oldZ = position.z;
	GLfloat newZPos = position.z + moveStep * 20;
	if (0.0 < newZPos)
		position.z = 0.0;
	else
		position.z = newZPos;

	camera->Move(F3dVector(0.0, 0.0, position.z - oldZ));
}

void Player::drawPlayer() {
	GLfloat x = position.x;
	GLfloat y = position.y;
	GLfloat z = position.z;

	glPushMatrix();
	glColor3f(0, 1, 0); // green

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

void Player::pickAnotherWeapon() {
	if (weapon == BASIC)
		weapon = FAST;
	else
		weapon = BASIC;
}