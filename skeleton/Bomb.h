#pragma once

#include "Particle.h"
#include "Enemy.h"

using namespace std;
using namespace physx;

class Bomb : public Particle
{
private:
	bool active = true;
	int life_;

public:
	Bomb(Vector3 pos, int life);

	void update(float t, vector<Enemy*>& v);
	void explode(vector<Enemy*>& v);
};

