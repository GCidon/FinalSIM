#include "Firework.h"

Firework::Firework(physx::PxShape* sh, Vector3 pos, int type) : Particle(sh, pos, 0, Vector4(0,255,0,0)) {
	pShape = sh;
	type_ = type;
	
	switch (type) {
	case 0:
		cant = 20;
		lifeFirst = 4;
		lifeSecond = 3;
		break;
	case 1:
		cant = 50;
		lifeFirst = 7;
		lifeSecond = 5;
		break;
	case 2:
		cant = 10;
		lifeFirst = 2;
		lifeSecond = 2;
		break;
	}
}

void Firework::explode() {
	for (int i = 0; i < cant; i++) {
		Vector3 ini = p;
		PxTransform* transform = new PxTransform(ini);
		Particle* p = new Particle(pShape, ini, 0, Vector4(0,255,0,0));
		if(type_ == 2)
			p->setVelocity(Vector3(rand() % 100 - 50, 50, rand() % 100 - 50));
		else if(type_ == 1)
			p->setVelocity(Vector3(rand() % 100 - 50, rand() % 100 - 50, 0));
		else p->setVelocity(Vector3(rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50));

		particulas.push_back(p);
	}
	active = false;
	Particle::~Particle();
}

void Firework::update(float t) {
	if (active) {
		Particle::integrate(t);
		if (getLifespan() > 4) {
			explode();
		}
	}
	for each (auto shot in particulas) {
		shot->integrate(t);
		if (shot->getLifespan() >= 3) {
			delete shot;
			shot = nullptr;
		}
	}
}
