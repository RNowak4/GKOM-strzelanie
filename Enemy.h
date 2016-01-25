#pragma once

#include "Alive.h"
#include "Camera.h"
#include "Color.h"
#include <ctime>

#include "Movable.h"

class Game;

class Enemy : public Movable, public Alive {
private:
	static const clock_t timeBetweenShot;
	static const SF3dVector defaultBulletVelocity;
	static const GLfloat defaultEnemyWidth;
	static const GLfloat defaultEnemyHeight;
	static const GLfloat defaultEnemyDepth;
	clock_t lastShot;
	Color color;
	Game* game;

public:
	Enemy(Game* game, const SF3dVector& position, const SF3dVector& velocity, const Color& color, unsigned health);
	
	~Enemy();

	void update();

	void display();
};

