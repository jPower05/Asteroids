// ===============================================
// @file   asteroids.h
// @author jpower
// @practical asteroids
// @brief  Main header file for PSP+GLFW asteroids game
// ===============================================

#ifndef ASTEROIDS_H
#define ASTEROIDS_H


#include "platform.h"

#include "../../common/core.h"
#include "GameObjects.h"

const float SPEED = 0.1f;
const float SHIP_MAX_ANGULAR_VELOCITY = 1000.0f*SPEED;
const float SHIP_MAX_ACCELERATION = 2.0f*SPEED;
const float SHIP_MAX_SPEED =1.5f*SPEED;
const float SHIP_FIRE_DELAY = 0.4f;

const float BULLET_DIE_DELAY = 1.0f;
const float BULLET_SPEED = 3.0f*SPEED;

const float ASTEROID_MAX_SPEED = 0.9f*SPEED;
const float ASTEROID_MIN_SPEED = 0.6f*SPEED;
const float ASTEROID_SPAWN_PROTECTION = 1.0f;

const float POWER_UP_SIZE = 10;
const int POWER_UP_TYPE_MAX_COUNT = 3;			//Number of powerup types 
extern PowerupPool powerups;

const int MAX_ENUM_TYPE = 4;
const float sizes [] = {1.0,0.75,0.5,0.25};
extern Ship ship;
extern BulletPool bullets;
extern AsteroidPool asteroids;

bool checkForBulletAsteroidCollision(const Vector2f bulletPoint,const Asteroid & asteroid);
bool checkForPointInCircle(const Vector2f point, const Vector2f centrePoint , const float radius);
bool checkForShipPowerupCollision(const Vector2f shipPosition, const Vector2f powerupPosition);
void spawnAsteroid(const Vector2f position,const int type);
void destroyAsteroid(Asteroid & asteroid,const int index);
void createPowerup(const Vector2f position,const int type);
void destroyPowerup(PowerUp & powerup,const int index);
void cullObjects();
#endif
