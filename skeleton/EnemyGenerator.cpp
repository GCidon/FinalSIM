#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator(Vector3 initPos, float period, float tam) {
	pos_ = initPos;
	period_ = period;
	tam_ = tam;
	timer_ = 0;
}

void EnemyGenerator::generate(float t, vector<Enemy*>& v) {
	timer_ += t;

	if (timer_ > period_) {
		BaseEnemy* p = new BaseEnemy(Vector3(pos_.x, pos_.y, (rand() % 50 - 0)-25));
		p->setVelocity(Vector3(0, -10, 0));
		v.push_back(p);
		timer_ = 0;
	}

}
