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
		int cosa = rand()%3+1;
		Enemy* p;
		switch (cosa) {
		case 1:
			p = new ShootingEnemy(Vector3(pos_.x, pos_.y, (rand() % 50 - 0)-25), 1);
			break;
		case 2:
			p = new BaseEnemy(Vector3(pos_.x, pos_.y, (rand() % 50 - 0) - 25));
			break;
		case 3:
			p = new SpringEnemy(Vector3(pos_.x, pos_.y, (rand() % 50 - 0) - 25));
			break;
		}
		p->setVelocity(Vector3(0, -10, 0));
		v.push_back(p);
		timer_ = 0;
	}

}
