#include "Enemy.h"
Enemy::~Enemy() {
	v_.clear();
}

ShootingEnemy::ShootingEnemy(Vector3 pos, float period) : Enemy(pos) {
	period_ = period;
	timer_ = 0;
}

void ShootingEnemy::update(float t) {
	timer_ += t;
	if (timer_ > period_) {
		Particle* part = new Particle(CreateShape(PxSphereGeometry(1)), p, 0, Vector4(20, 10, 0, 1));
		part->setVelocity(Vector3(0, -30, 0));
		v_.push_back(part);
		timer_ = 0;
	}
}

SpringEnemy::SpringEnemy(Vector3 pos) : Enemy(pos) {
	center_ = new Particle(CreateShape(PxSphereGeometry(0.05)), pos+Vector3(0,0,5), 0, Vector4(0, 0, 0, 0));
	center_->setVelocity(Vector3(0,-10,0));
	spring_ = new ParticleSpring(center_, 50.0, 0);
}

SpringEnemy::~SpringEnemy() {
	delete center_;
	delete spring_;
}

void SpringEnemy::update(float t) {
	center_->integrate(t);
	spring_->updateForce(this, t);
}