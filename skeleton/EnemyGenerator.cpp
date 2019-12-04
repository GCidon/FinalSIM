#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator(Vector3 initPos, float period, float tam) {
	pos_ = initPos;
	period_ = period;
	tam_ = tam;
	timer_ = 0;
}

void EnemyGenerator::generate(float t, vector<Particle*>& v) {
	timer_ += t;

	if (timer_ > period_) {
		Particle* p = new Particle(CreateShape(PxSphereGeometry(2)), Vector3(pos_.x, pos_.y, (rand() % 50 - 0)-25), 0, Vector4(255, 0, 0, 0));
		p->setVelocity(Vector3(0, -10, 0));
		v.push_back(p);
		timer_ = 0;
	}

}
