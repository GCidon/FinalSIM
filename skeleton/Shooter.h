#pragma once
#include "Particle.h"
class Shooter :
	public Particle
{
private:
	float period_;
	float timer_;
	float dir_;

public:
	Shooter(float period, Vector3 pos, float dir);

	void generate(float t, vector <Particle*>& v);
};

