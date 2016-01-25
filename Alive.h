#pragma once

class Alive {
protected:
	int health;

public:
	Alive(unsigned health);

	~Alive();

	void damage(unsigned dmg);

	int getHealth() const;
};

