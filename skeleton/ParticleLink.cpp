#include "ParticleLink.h"

float ParticleLink::currentLength() const {
	Vector3 relativePos = particle[0]->getPosition() - particle[1]->getPosition();
	return relativePos.magnitude();
}

unsigned ParticleCable::addContact(ParticleContact* contact, unsigned limit) const {
	float length = currentLength();

	if (length < maxLength) {
		return 0;
	}

	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];

	// Calculate the normal.

	Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
	normal.normalize();

	// Add information to contact: normal, penetration & restitution.
	contact->contactNormal = normal;
	contact->penetration = length - maxLength;
	contact->restitution = restitution;

	return 1;
}

unsigned ParticleRod::addContact(ParticleContact* contact, unsigned limit) const {

	float currentLen = currentLength();

	if (currentLen == length) {
		return 0;
	}

	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];

	// Calculate the normal
	Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
	normal.normalize();

	// The contact normal depends on whether we’re extending or compressing
	if (currentLen > length) {
		contact->contactNormal = normal;
		contact->penetration = currentLen - length;
	}
	else {
		contact->contactNormal = -normal;
		contact->penetration = length - currentLen;
	}

	// Always use zero restitution (no bounciness)
	contact->restitution = 0;

	return 1;
}