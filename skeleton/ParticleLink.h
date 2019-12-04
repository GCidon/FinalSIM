#pragma once
#include "ParticleContact.h"

class ParticleLink
{
public:
	Particle* particle[2];

	virtual unsigned addContact(ParticleContact* contact, unsigned limit) const = 0;
protected:
	float currentLength() const;

};

class ParticleCable : public ParticleLink {
public:
	ParticleCable(Particle* p1, Particle* p2, float max, float res) : maxLength(max), restitution(res) {
		particle[0] = p1;
		particle[1] = p2;
	}
	float maxLength;
	float restitution;
	virtual unsigned addContact(ParticleContact* contact, unsigned limit) const;
};

class ParticleRod : public ParticleLink {
public:
	ParticleRod(Particle* p1, Particle* p2, float len) : length(len) {
		particle[0] = p1;
		particle[1] = p2;
	}
	float length;
	virtual unsigned addContact(ParticleContact* contact, unsigned limit) const;
};

