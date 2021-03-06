#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	Particle lascoll;
	Particle lascoll2;
	Particle lascoll3;
	Particle lascoll4;
	Particle explosionturret;
	Particle soldierexplosion;
	Particle tankexplosion;
	Particle playerexplosion;

	Particle trilaser;

	Particle laser;
	Particle laser0;
	Particle laser22_5;
	Particle laser45;
	Particle laser67_5;
	Particle laser90;
	Particle laser112_5;
	Particle laser135;
	Particle laser157_5;
	Particle laser180;
	Particle laser202_5;
	Particle laser225;
	Particle laser247_5;
	Particle laser270;
	Particle laser292_5;
	Particle laser315;
	Particle laser337_5;

	Particle poweredlaser;
	Particle poweredlaser0;
	Particle poweredlaser22_5;
	Particle poweredlaser45;
	Particle poweredlaser67_5;
	Particle poweredlaser90;
	Particle poweredlaser112_5;
	Particle poweredlaser135;
	Particle poweredlaser157_5;
	Particle poweredlaser180;
	Particle poweredlaser202_5;
	Particle poweredlaser225;
	Particle poweredlaser247_5;
	Particle poweredlaser270;
	Particle poweredlaser292_5;
	Particle poweredlaser315;
	Particle poweredlaser337_5;

	Particle balllaser;
	Particle balllaser0;
	Particle balllaser22_5;
	Particle balllaser45;
	Particle balllaser67_5;
	Particle balllaser90;
	Particle balllaser112_5;
	Particle balllaser135;
	Particle balllaser157_5;
	Particle balllaser180;
	Particle balllaser202_5;
	Particle balllaser225;
	Particle balllaser247_5;
	Particle balllaser270;
	Particle balllaser292_5;
	Particle balllaser315;
	Particle balllaser337_5;

	Particle laserweaponshoot0;
	Particle laserweaponshoot22_5;
	Particle laserweaponshoot45;
	Particle laserweaponshoot67_5;
	Particle laserweaponshoot90;
	Particle laserweaponshoot112_5;
	Particle laserweaponshoot135;
	Particle laserweaponshoot157_5;
	Particle laserweaponshoot180;
	Particle laserweaponshoot202_5;
	Particle laserweaponshoot225;
	Particle laserweaponshoot247_5;
	Particle laserweaponshoot270;
	Particle laserweaponshoot292_5;
	Particle laserweaponshoot315;
	Particle laserweaponshoot337_5;
	
	Particle Frontthreeshoot;
	Particle Leftthreeshoot;
	Particle Rightthreeshoot;

	Particle Frontthreeshootonepowerup;
	Particle Leftthreeshootonepowerup;
	Particle Rightthreeshootonepowerup;

	Particle Frontthreeshoottwopowerup;
	Particle Leftthreeshoottwopowerup;
	Particle Rightthreeshoottwopowerup;

	Particle enemyshoot;
	Particle enemymissile;

	Particle bosslaser1;
	Particle bosslaser2;
};

#endif // __MODULEPARTICLES_H__