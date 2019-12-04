#pragma once

#include "RenderUtils.hpp"

using namespace physx;
using namespace std;

class Particle {

protected:
	RenderItem* item;
	PxTransform* transform;
	Vector3 p;
	Vector3 v;
	Vector3 a;
	Vector3 force;
	float speed;
	float damping;
	float inverse_mass;
	float lifespan = 0;

public:

	Particle(physx::PxShape* sh, Vector3 pos, int type, Vector4 color);
	~Particle();

	void integrate(float t);

	float getMass();
	float getInverseMass();
	Vector3 getPosition();
	Vector3 getVelocity();
	Vector3 getAcceleration();
	float getDamping();
	float getLifespan();
	void clearForce();
	void addForce(const Vector3& f);

	void setMass(float m);
	void setPosition(Vector3 velo);
	void setVelocity(Vector3 velo);
	void setAcceleration(Vector3 velo);
	void setDamping(float m);
};
