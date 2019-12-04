#include "Particle.h"

Particle::Particle(physx::PxShape* sh, Vector3 pos, int type, Vector4 color)
{
	p = pos;
	transform = new PxTransform(pos);
	force = Vector3(0.0, 0.0, 0.0);
	item = new RenderItem(sh, transform, color);
	speed = 1;
	switch (type) {
	case 0:
		setMass(10.0f); 
		setVelocity(Vector3(0.0f, 0.0f, 0.0f)); 
		setAcceleration(Vector3(0.0f, 0.0f, 0.0f));
		setDamping(0.99f);
		break;
	case 1:
		setMass(200.0f); // 200.0 Kg
		setVelocity(Vector3(0.0f, 0.0f, 0.0f));
		setAcceleration(Vector3(0.0f, 0.0f, 0.0f));
		setDamping(0.99f);
		break;
	}
}

Particle::~Particle() {
	delete transform;
	item->release();
}

void Particle::clearForce() {
	force = Vector3(0.0, 0.0, 0.0);
}

void Particle::addForce(const Vector3& f) {
	force += f;
}

void Particle::integrate(float t) {
	if (inverse_mass <= 0.0f) return;
	p += v * speed * t;
	Vector3 totalAcc = a;
	totalAcc += force * inverse_mass;
	v += totalAcc * t;
	v *= powf(damping, t);
	*transform = PxTransform(p);
	clearForce();
	lifespan += t;
}

float Particle::getInverseMass() {
	return 1 / inverse_mass;
}

float Particle::getMass() {
	return 1 / inverse_mass;
}

Vector3 Particle::getPosition() {
	return p;
}

Vector3 Particle::getVelocity() {
	return v;
}

Vector3 Particle::getAcceleration() {
	return a;
}

float Particle::getDamping() {
	return damping;
}

float Particle::getLifespan() {
	return lifespan;
}


void Particle::setPosition(Vector3 velo) {
	p = velo;
	*transform = PxTransform(p);
}

void Particle::setMass(float m) {
	inverse_mass = 1 / m;
}

void Particle::setVelocity(Vector3 velo) {
	v = velo;
}

void Particle::setAcceleration(Vector3 velo) {
	a = velo;
}

void Particle::setDamping(float m) {
	damping = m;
}
