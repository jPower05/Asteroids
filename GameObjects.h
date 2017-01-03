// ===============================================
// @file   GameObjects.h
// @author jpower
// @practical asteroids
// @brief  Main file for PSP+GLFW asteroids game
// ===============================================

#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "../../common/core.h"
#include "../../common/Pool.h"

const float ASTEROID_SCALE = 0.1f;
const int ASTEROID_GRANULARITY = 20;
const float ASTEROID_MAX_RADIUS = 1.2f;
const float ASTEROID_MIN_RADIUS = 0.8f;
const float ASTEROID_ANGLE_VARABILITY = 0.5f;

// ======================================
// BaseGameObject
// ======================================

class BaseGameObject {
public:
	enum State {ASLEEP, ALIVE, DEAD};
	State state;
		
	float damping;
	Vector2f position;
	Vector2f velocity;
	Vector2f acceleration;
	float radius;	
	float angle;
	float angularVelocity;
	float angularAcceleration;
	
	virtual void render() = 0;
	virtual void update(float dt);
	virtual void reset();
	virtual void wrap(); 	//used for wrapping game objects
};

// ======================================
// Ship
// ======================================

class Ship: public BaseGameObject {
	float firingTime;
	int health;
	int bulletsRemaining;
public:
	bool shoot;			//boolean to check can you fire bullet
	void render();
	void update(float dt);
	void reset();
	void shootBullet();
	bool checkCanFire();
};

// ======================================
// PowerUps
// ======================================

class PowerUp: public BaseGameObject {
public:	
	float x;
	float y;
	int enumIndex;
	enum Type {TELEPORT, MORE_BULLETS, REPEL};
	Type type;

	void render();
	void reset();
	void update(float dt);
	int getEnumIndex();
};
typedef Pool<PowerUp> PowerupPool;
// ======================================
// Bullet
// ======================================

class Bullet: public BaseGameObject {
	float timeToDie;
public:
	void render();
	void reset();
	void update(float dt);
};

typedef Pool<Bullet> BulletPool;

// ======================================
// Asteroid
// ======================================

class Asteroid: public BaseGameObject {
	
public:
	int enumIndex;
	enum Type {LARGE, MEDIUM, SMALL, TINY};
	Type type;
	  
	float size;
	float spawn_protection;
	bool invincible;
	Vector2f vertices[ASTEROID_GRANULARITY];
	Vector2f angles[ASTEROID_GRANULARITY];
	void render();
	void reset();
	void update(float dt);
	int getEnumIndex();
	void wrap();
};

typedef Pool<Asteroid> AsteroidPool;


#endif
