#pragma once
#include "Particle.h"

class ParticleContact
{
public:
	Particle* particle[2];
	float restitution;
	Vector3 contactNormal;
	float penetration;
	float calculateSeparatingVelocity();
	void resolve(float t);
	ParticleContact(Particle* p1, Particle* p2, float res);

protected:

	void resolveInterpenetration(float t);

private:
	void resolveVelocity(float t);
};

