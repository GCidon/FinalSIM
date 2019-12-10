#include "Bomb.h"

Bomb::Bomb(Vector3 pos, int life) : Particle(CreateShape(PxSphereGeometry(1)), pos, 0, Vector4(0,0,255,0)) {
	life_ = life;
	setVelocity(Vector3(0, 30, 0));
}

void Bomb::update(float t, vector<Enemy*>& v) {
	if (active) {
		Particle::integrate(t);
		if (getLifespan() > life_)
			explode(v);
	}
}

void Bomb::explode(vector<Enemy*>& v) {
	for (auto obj : v) {
		if ((obj->getPosition() - getPosition()).normalize() < 20) {
			obj->addForce((obj->getPosition() - getPosition()).getNormalized() * 5000);
		}
	}
}