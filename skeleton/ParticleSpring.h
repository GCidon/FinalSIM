#pragma once
#include "Particle.h"
class ParticleSpring
{
private:
	Particle* other_;
	float k_;
	float restLength_;

public:
	ParticleSpring(Particle* o, float k, float restLength) {
		other_ = o;
		k_ = k;
		restLength_ = restLength;
	}

	virtual void updateForce(Particle* particle, float t);
};

