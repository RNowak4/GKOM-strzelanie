#include "Bullet.h"
#include "Camera.h"
#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include <windows.h>

#define SQR(x) (x*x)

const clock_t Game::timeStep = 30L;
const clock_t Game::timeBetweenStep = 30000L;
const clock_t Game::startTimeDiff = 1000L;
const GLfloat Game::depth = 24.0;

Game::Game() : lastGeneratedEnemy(0), enemyGenerationDiff(startTimeDiff), 
lastChangedMap(0), mapScrollSpeed(0.2), lastGeneratedEnemyType(STANDARD) {
	
	leftDownCorner = F3dVector(-0.24, -0.07, 0.0);
	rightDownCorner = F3dVector(0.24, -0.07, 0.0);
	leftUpCorner = F3dVector(-0.24, 0.07, 0.0);
	rightUpCorner = F3dVector(0.24, 0.07,  0.0);

	player = new Player(F3dVector(0.0, 0.0, 0.0), this, 100);

	for (int i = 0; i < 256; ++i)
		keys[i] = false;
}

Game::~Game() {
}

void Game::update() {
	checkCollisions();
	generateEnemy();

	if (keys[' '] == true) 
		player->shoot();

	if (keys['a'])
		player->moveLeft();

	if (keys['d'])
		player->moveRight();

	if (keys['w'])
		player->moveForward();

	if (keys['s'])
		player->moveBackward();

	if (keys['q'])
		player->pickAnotherWeapon();

	for (auto bullet : bullets) {
		bullet->update();
	}

	for (auto enemy : enemies) {
		enemy->update();
	}

	player->update();
}

GLfloat fRand(GLfloat fMin, GLfloat fMax) {
	GLfloat f = (GLfloat)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void Game::generateEnemy() {
	clock_t currentTime = clock();
	if (currentTime - lastGeneratedEnemy > enemyGenerationDiff) {
		lastGeneratedEnemy = currentTime;

		GLfloat x = fRand(leftDownCorner.x, rightDownCorner.x);
		auto position = F3dVector(x, 0, -depth);
		auto velocity = F3dVector(0.0, 0.0, fRand(0.02, 0.15));
		auto red = Color(0.05, 0.9, 0.05);

		Enemy* newEnemy = new Enemy(this, position, velocity, red, 100);
		enemies.push_back(shared_ptr<Enemy>(newEnemy));
	}
}

void Game::display() {
	player->display();

	for (auto bullet : bullets)
		bullet->display();

	for (auto enemy : enemies)
		enemy->display();

	displayBoard();
}

bool Game::isOutOfMap(shared_ptr<Bullet> bullet) const {
	if (bullet->getPosition().z < 0.0 ||
		bullet->getPosition().z > rightUpCorner.z)
		return true;

	return false;
}

Player* Game::getPlayer() {
	return player;
}

GLfloat Game::getLeftBorder() const {
	return leftDownCorner.x;
}

GLfloat Game::getRightBorder() const {
	return rightDownCorner.x;
}

void Game::displayBoard() {
	glPushMatrix();
	glColor3f(1, 0, 1);

	glBegin(GL_LINES);
		glVertex3f(leftDownCorner.x, leftDownCorner.y, 0.0);
		glVertex3f(leftDownCorner.x, leftDownCorner.y, -depth);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(leftUpCorner.x, leftUpCorner.y, 0.0);
		glVertex3f(leftUpCorner.x, leftUpCorner.y, -depth);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(rightDownCorner.x, rightDownCorner.y, 0.0);
		glVertex3f(rightDownCorner.x, rightDownCorner.y, -depth);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(rightUpCorner.x, rightUpCorner.y, 0.0);
		glVertex3f(rightUpCorner.x, rightUpCorner.y, -depth);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glVertex3f(rightUpCorner.x, rightUpCorner.y, -depth);
		glVertex3f(leftUpCorner.x, leftUpCorner.y, -depth);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(rightDownCorner.x, rightDownCorner.y, -depth);
		glVertex3f(leftDownCorner.x, leftDownCorner.y, -depth);
	glEnd();

	glColor3f(0.25, 0.25, 0.25);
	if (lastChangedMap > 0.0)
		lastChangedMap = -1.0;
	for (GLfloat i = lastChangedMap; i > -depth; i -= 1.0) {
		glBegin(GL_LINES);
			glVertex3f(rightDownCorner.x, rightDownCorner.y, i);
			glVertex3f(leftDownCorner.x, leftDownCorner.y, i);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(rightDownCorner.x, rightUpCorner.y, i);
			glVertex3f(leftDownCorner.x, leftUpCorner.y, i);
		glEnd();
	}
	lastChangedMap += mapScrollSpeed;

	for (GLfloat i = leftDownCorner.x; i < rightDownCorner.x; i += 0.025) {
		glBegin(GL_LINES);
			glVertex3f(i, rightUpCorner.y, 0);
			glVertex3f(i, leftUpCorner.y, -depth);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(i, rightDownCorner.y, 0);
			glVertex3f(i, leftDownCorner.y, -depth);
		glEnd();
	}

	glPopMatrix();
}

// default
void Game::createBullet(const SF3dVector& position, const SF3dVector& velocity, bool isHostile) {
	Bullet *newBullet = new Bullet(position, velocity, 0.01, 0.01, 0.01, 50, isHostile);
	bullets.push_back(shared_ptr<Bullet>(newBullet));
}

void Game::createBullet(const SF3dVector& position, const SF3dVector& velocity, GLfloat width, GLfloat height, GLfloat depth, unsigned damage, bool isHostile) {
	Bullet *newBullet = new Bullet(position, velocity, width, height, depth, damage, isHostile);
	bullets.push_back(shared_ptr<Bullet>(newBullet));
}

void Game::setKey(unsigned char key, bool status) {
	keys[key] = status;
}

GLfloat Game::getDepth() {
	return depth;
}

void Game::checkCollisions() {
	list<list<shared_ptr<Bullet> >::iterator> bulletsToRemove;
	list<list<shared_ptr<Enemy> >::iterator> enemiesToRemove;

	for (auto it = bullets.begin(); it != bullets.end(); ++it) {
		if ((*it)->getPosZ() > 0 || (*it)->getPosZ() < -this->getDepth())
			bulletsToRemove.push_back(it);
		else {
			for (auto eIt = enemies.begin(); eIt != enemies.end(); ++eIt) {
				if (!(*it)->isHostile() && isColliding(*it, *eIt)) {
					bulletsToRemove.push_back(it);
					(*eIt)->damage((*it)->getDamage());
					if ((*eIt)->getHealth() <= 0)
						enemiesToRemove.push_back(eIt);
				}
			}
		}
	}

	for (auto it : bulletsToRemove)
		bullets.erase(it);

	for (auto it : enemiesToRemove)
		enemies.erase(it);
}

bool Game::isColliding(shared_ptr<Coordinable> bullet, shared_ptr<Coordinable> enemy) {
	auto bulletPosition = bullet->getPosition();
	auto enemyPosition = enemy->getPosition();

	// usprawnic jak starczy czasu
	if (bulletPosition.z <= enemyPosition.z  &&
		bulletPosition.z >= enemyPosition.z - enemy->getDepth() &&
		bulletPosition.y <= enemyPosition.y + enemy->getHeight() / 2 &&
		bulletPosition.y >= enemyPosition.y - enemy->getHeight() / 2 &&
		bulletPosition.x <= enemyPosition.x + enemy->getWidth() / 2 &&
		bulletPosition.x >= enemyPosition.x - enemy->getWidth() / 2)
		return true;

	return false;
}