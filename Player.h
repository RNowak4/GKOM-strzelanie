#pragma once

#include "Movable.h"
#include "Alive.h"
#include <ctime>

class Game;

enum Weapon {
	BASIC,
	FAST
};

// TODO dynamiczna zmiana koloru
class Player : public Movable, public Alive {
private:
	static const clock_t timeBetweenBasicShot;
	static const clock_t timeBetweenFastShot;
	static const GLfloat defaultPlayerWidth;
	static const GLfloat defaultPlayerHeight;
	static const GLfloat defaultPlayerDepth;
	static const GLfloat moveStep;
	static const SF3dVector defaultBulletVelocity;
	Camera* camera;
	clock_t lastShot;
	Game* game;
	Weapon weapon;

	void drawPlayer(); // rysowanie "statku"

	bool canShoot(const clock_t currentTime) const;

public:
	Player(const SF3dVector& position, Game* game, unsigned health);
	
	~Player();

	void update();

	void display();

	void shoot();

	void moveLeft();

	void moveRight();

	void moveForward();

	void moveBackward();

	void pickAnotherWeapon();
};

