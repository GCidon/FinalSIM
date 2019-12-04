#pragma once

#include "Particle.h"
#include "ParticleLink.h"

class Player
{
protected:
	Particle* body;
	Particle* shooter;
	ParticleCable* cable;
	ParticleContact* contact;

public:
	Player();
	~Player();

	Particle* getBody();
	Particle* getShooter();
	ParticleCable* getCable();
	ParticleContact* getContact();

};

