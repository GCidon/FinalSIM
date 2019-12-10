#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"
#include "Player.h"
#include "EnemyGenerator.h"
#include "Firework.h"
#include "Bomb.h"
#include <vector>
#include "callbacks.hpp"
#include <iostream>

using namespace std;
using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

PxShape* esferashape = NULL;

Player* player = NULL;

EnemyGenerator* gen = NULL;

vector<Enemy*> enemies;
vector<Particle*> bullets;
vector<Particle*> enemBullets;
vector<Firework*> fireworks;
vector<Bomb*> bombs;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	esferashape = CreateShape(PxSphereGeometry(2));

	player = new Player();

	gen = new EnemyGenerator(Vector3(0, 50, 0), 0.75, 25);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	// ------------------------------------------------------
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	if (player->getCable()->addContact(player->getContact(), 0))
		player->getContact()->resolve(t);

	player->getShooter()->integrate(t);
	player->getShooter()->generate(t, bullets);

	gen->generate(t, enemies);
	for (auto bul : bullets) bul->integrate(t);
	for (auto bomb : bombs) bomb->update(t, enemies);

	auto obj = enemies.begin();
	while (obj!= enemies.end() && !enemies.empty()) {
		Enemy* aux = *obj;

		aux->integrate(t);
		aux->update(t);

		if ((player->getBody()->getPosition() - aux->getPosition()).normalize() < 4) {
			Firework* newFire = new Firework(CreateShape(PxSphereGeometry(0.2)), player->getBody()->getPosition(), 0);
			fireworks.push_back(newFire);
			newFire->explode();

			player->getBody()->setPosition(Vector3(0, 0, 0));
			player->getShooter()->setPosition(Vector3(0, 0, 0));
		}

		for (auto bul : aux->v_) {
			bul->integrate(t);
			if ((player->getBody()->getPosition() - bul->getPosition()).normalize() < 2) {
				Firework* newFire = new Firework(CreateShape(PxSphereGeometry(0.2)), player->getBody()->getPosition(), 0);
				fireworks.push_back(newFire);
				newFire->explode();

				player->getBody()->setPosition(Vector3(0, 0, 0));
				player->getShooter()->setPosition(Vector3(0, 0, 0));
			}
		}

		int i = 0;
		bool deleted = false;
		while (i < bullets.size() && !deleted) {
			auto bul = bullets[i];
			if ((bul->getPosition() - aux->getPosition()).normalize() < 2) {
				Firework* newFire = new Firework(CreateShape(PxSphereGeometry(0.2)), aux->getPosition(), 2);
				fireworks.push_back(newFire);
				newFire->explode();

				for (auto enemBul : aux->v_) delete enemBul;

				enemies.erase(obj);
				delete aux;
				obj = enemies.begin();
				deleted = true;

				
			}
			i++;
		}

		if (!deleted && (aux->getPosition().y < -10 || aux->getPosition().z < -30 || aux->getPosition().z > 30)) {
			for (auto enemBul : aux->v_) delete enemBul;
			enemies.erase(obj);
			delete aux;
			obj = enemies.begin();
			deleted = true;
		}


		if (!enemies.empty() && !deleted)
			obj++;

	}

	for (auto obj : fireworks) obj->update(t);


	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
}

void throwBomb() {
	Bomb* b = new Bomb(player->getBody()->getPosition(), 1);
	bombs.push_back(b);
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
		case 'I':
		{
			if (player->getBody()->getPosition().y < 25)
				player->getBody()->setPosition(player->getBody()->getPosition() + Vector3(0, 1, 0));
			break;
		}
		case 'K':
		{
			if (player->getBody()->getPosition().y > 0)
				player->getBody()->setPosition(player->getBody()->getPosition() + Vector3(0, -1, 0));
			break;
		}
		case 'J':
		{
			if(player->getBody()->getPosition().z > -25)
				player->getBody()->setPosition(player->getBody()->getPosition() + Vector3(0, 0, -1));
			break;
		}
		case 'L':
		{
			if(player->getBody()->getPosition().z < 25)
				player->getBody()->setPosition(player->getBody()->getPosition() + Vector3(0, 0, 1));
			break;
		}
		case 'B':
		{
			throwBomb();
			break;
		}
		default:
			break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}