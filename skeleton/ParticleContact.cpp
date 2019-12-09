#include "ParticleContact.h"

ParticleContact::ParticleContact(Particle* p1, Particle* p2, float res) {
	particle[0] = p1;
	particle[1] = p2;

	restitution = res;

	contactNormal = particle[0]->getPosition() - particle[1]->getPosition();
}

void ParticleContact::resolve(float t) {
	resolveVelocity(t);
	resolveInterpenetration(t);
}

float ParticleContact::calculateSeparatingVelocity() {
	/*float res;
	float veloa = particle[0]->getVelocity().x * (particle[1]->getPosition() - particle[0]->getPosition()).x +
		particle[0]->getVelocity().y * (particle[1]->getPosition() - particle[0]->getPosition()).y +
		particle[0]->getVelocity().z * (particle[1]->getPosition() - particle[0]->getPosition()).z;
	float velob = particle[1]->getVelocity().x * (particle[0]->getPosition() - particle[1]->getPosition()).x +
		particle[1]->getVelocity().y * (particle[0]->getPosition() - particle[1]->getPosition()).y +
		particle[1]->getVelocity().z * (particle[0]->getPosition() - particle[1]->getPosition()).z;
	res = veloa + velob;
	return -res;*/

	Vector3 relativeVelocity = particle[0]->getVelocity();
	if (particle[1]) relativeVelocity -= particle[1]->getVelocity();
	return relativeVelocity.dot(contactNormal);

}

void ParticleContact::resolveVelocity(float t) {
	// Get current separating velocity
	float sVelocity = calculateSeparatingVelocity();

	if (sVelocity > 0) return;
	// Compute separating velocity after collision
	float colVelocity = -sVelocity * restitution;
	float finalVelocity = colVelocity - sVelocity;
	// Compute total impulse
	float impulso = finalVelocity / (particle[0]->getInverseMass() + particle[1]->getInverseMass());
	// Compute impulse for each particle
	Vector3 impulsoVec = contactNormal * impulso;
	// Set new velocity for each particle
	particle[1]->setVelocity(particle[1]->getVelocity() + impulsoVec * -particle[1]->getInverseMass());

}

void ParticleContact::resolveInterpenetration(float t) {
	// Check if there is interpenetration
	if (penetration >= 0) {
		// Calculate factor of each particle depending on mass
		float totalMass = particle[0]->getInverseMass() + particle[1]->getInverseMass();
		// Calculate the movement for each particle
		Vector3 movement = contactNormal * (-penetration / totalMass);
		// Apply movement to the position of each particle
		particle[1]->setPosition(particle[1]->getPosition() + movement * particle[1]->getInverseMass());
	}
}