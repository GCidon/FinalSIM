#pragma once
#include "Particle.h"
#include "ParticleSpring.h"
class Enemy :
	public Particle
{
public:
	Enemy(Vector3 pos) : Particle(CreateShape(PxSphereGeometry(2)), pos, 0, Vector4(255, 0, 0, 0)) {}
	~Enemy();

	virtual void update(float t) = 0;
	vector<Particle*> v_;
};

class BaseEnemy : public Enemy 
{
public:
	BaseEnemy(Vector3 pos) : Enemy(pos) {}
	virtual void update(float t) {}
};

class ShootingEnemy : public Enemy 
{
protected:
	float period_;
	float timer_;
public:
	ShootingEnemy(Vector3 pos, float period);
	~ShootingEnemy();
	virtual void update(float t);
};

class SpringEnemy : public Enemy 
{
protected:
	ParticleSpring* spring_;
	Particle* center_;
public:
	SpringEnemy(Vector3 pos);
	~SpringEnemy();
	virtual void update(float t);

};

