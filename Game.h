#pragma once

#include "Sphere.h"
#include "glut.h"
#include <ctime>
#include <list>
#include <memory>

using namespace std;

class Camera;
class Coordinable;
class Enemy;
class Bullet;
class Player;
struct SF3dVector;

// TODO
// pon {
// 1 detekcja zderzen V
// 2 end game
// 3 generowanie wrogow
// 3a przyspieszenie generowania wrogow
// generowanie bonusow
// }
// wt { 
// informacje o nabojach
// 2-3 typy wrogow
// }

enum EnemyType {
	STANDARD,
	FASTER
	//BOSS
};

class Game {
private:
	static const clock_t timeBetweenStep; // ms
	static const clock_t timeStep;
	static const clock_t startTimeDiff;
	static const GLfloat depth;
	bool keys[256];
	clock_t enemyGenerationDiff;
	clock_t lastGeneratedEnemy;
	EnemyType lastGeneratedEnemyType;
	GLfloat lastChangedMap;
	GLfloat mapScrollSpeed;
	Player *player;
	SF3dVector leftDownCorner;
	SF3dVector leftUpCorner;
	SF3dVector rightDownCorner;
	SF3dVector rightUpCorner;
	list<shared_ptr<Bullet> > bullets;
	list<shared_ptr<Enemy> > enemies;

	bool isOutOfMap(shared_ptr<Bullet> bullet) const;

	bool isGameEnd() const;

	void displayBoard();

	void checkCollisions();

	void generateEnemy();

	static bool isColliding(shared_ptr<Coordinable> bullet, shared_ptr<Coordinable> enemy);

public:
	Game();

	~Game();

	void prepareGame(int argc, char **argv) const;

	// Update dla Game i dla wszystkich elementow gry
	void update();

	void display();

	void createBullet(const SF3dVector& position, const SF3dVector& velocity, bool isHostile);

	void createBullet(const SF3dVector& position, const SF3dVector& velocity, GLfloat width, GLfloat height, GLfloat depth, unsigned damage, bool isHostile);

	Player* getPlayer();

	GLfloat getDepth();

	GLfloat getLeftBorder() const;

	GLfloat getRightBorder() const;

	void setKey(unsigned char key, bool status);
};

