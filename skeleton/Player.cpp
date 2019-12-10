#include "Player.h"

Player::Player() {
	body = new Particle(CreateShape(PxSphereGeometry(2)), Vector3(0, 5, 0), 0, Vector4(0, 0, 255, 0));
	shooter = new Shooter(1, Vector3(0,0,0), 30);
	shooter->setAcceleration(Vector3(0, -9.8, 0.0));
	cable = new ParticleCable(body, shooter, 5, 0.5);
	contact = new ParticleContact(body, shooter, 0.5);
}

Particle* Player::getBody() {
	return body;
}

Shooter* Player::getShooter() {
	return shooter;
}

ParticleCable* Player::getCable() {
	return cable;
}

ParticleContact* Player::getContact() {
	return contact;
}