#pragma once

#include "Particle.h"

class EnemyGenerator
{
private:
	Vector3 pos_;
	float period_;
	float timer_;
	float tam_;

public:
	EnemyGenerator(Vector3 initPos, float period, float tam);

	void generate(float t, vector<Particle*>& v);
};

