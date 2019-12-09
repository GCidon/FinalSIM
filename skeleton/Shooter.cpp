#include "Shooter.h"

Shooter::Shooter(float period, Vector3 pos, float dir) : Particle(CreateShape(PxBoxGeometry(2, 2, 2)), pos, 0, Vector4(0, 255, 0, 0)) {
	period_ = period;
	timer_ = 0;
	dir_ = dir;
}

void Shooter::generate(float t, vector<Particle*>& v) {
	timer_ += t;
	if (timer_ > period_) {
		Particle* part = new Particle(CreateShape(PxSphereGeometry(1)), p, 0, Vector4(0,10,10,1));
		part->setVelocity(Vector3(0, dir_, (rand()%20-1)-10));
		v.push_back(part);
		timer_ = 0;
	}
}
