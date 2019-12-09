#pragma once

#include "Particle.h"
#include "ParticleLink.h"
#include "Shooter.h"

class Player
{
protected:
	Particle* body;
	Shooter* shooter;
	ParticleCable* cable;
	ParticleContact* contact;

public:
	Player();
	~Player();

	Particle* getBody();
	Shooter* getShooter();
	ParticleCable* getCable();
	ParticleContact* getContact();

};

