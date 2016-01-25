#include "Alive.h"


Alive::Alive(unsigned health) : health(health) {
}

Alive::~Alive() {
}

void Alive::damage(unsigned dmg) {
	health -= dmg;
}

int Alive::getHealth() const {
	return health;
}