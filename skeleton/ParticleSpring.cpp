#include "ParticleSpring.h"

void ParticleSpring::updateForce(Particle* particle, float t) {
	Vector3 f = particle->getPosition();
	f -= other_->getPosition();

	float length = f.normalize();

	float deltaL = (length - restLength_);
	float forceMargnitude = -k_ * deltaL;
	f *= forceMargnitude;
	particle->addForce(f);
}
