// ===============================================
// @file   GameObjects.cpp
// @author jpower
// @practical asteroids
// @brief  Main file for PSP+GLFW asteroids game
// ===============================================


#include "asteroids.h"
#include "GameObjects.h"
#include <cmath>
// ======================================
// BaseGameObject
// ======================================
 
void BaseGameObject::update(float dt) {
	// linear movement
	velocity += dt*acceleration;
	position += dt*velocity;
	velocity *= pow(damping, dt);
	
	//anglular movement
	angle += dt*angularVelocity;
	if(angle < 0)angle += 360;
	if(angle > 360) angle -= 360;
}

void BaseGameObject::wrap(){
	//check if a game object needs to be wrapped
	if(position.x > ASPECT)position.x = 0.1;
	else if(position.x < 0) position.x = ASPECT - 0.1;
	else if(position.y > 1)position.y = 0.1;
	else if(position.y < 0)position.y = 0.9;
}


void BaseGameObject::reset() {
	state = BaseGameObject::ALIVE;
	velocity = Vector2f::ZERO;
	position = Vector2f::ZERO;
	acceleration = Vector2f::ZERO;
	angle = 0;
	radius = 1;
	angularVelocity = 0;
	damping = 1;
}



// ======================================
// Ship
// ======================================

void Ship::reset() {
	BaseGameObject::reset();
	
	position = Vector2f(ASPECT/2,0.5);
	damping = 0.8;
	
	firingTime = 0;
	
	//health = 100;
	//bulletsRemaining = 20;
}

void Ship::update(float dt) {
	// TODO - update position (using base class)
	BaseGameObject::update(dt);
	
	// TODO - process ship control events (update velocity)
	
	//Allow ship to fire bullet
	if (checkCanFire()){
		shootBullet();
	}
	else firingTime -= dt;


	
	//see if need to wrap game object
	if(position.x > ASPECT)position.x = 0.1;
	else if(position.x < 0) position.x = ASPECT - 0.1;
	else if(position.y > 1)position.y = 0.1;
	else if(position.y < 0)position.y = 0.9;
}
// ======================================
// Powerup
// ======================================

void PowerUp::reset(){
	BaseGameObject::reset();

	//set enum index
	enumIndex = getEnumIndex();

}

void PowerUp::update(float dt) {
	
	BaseGameObject::update(dt);
	
}


int PowerUp::getEnumIndex(){
	for(int k = 0; k < MAX_ENUM_TYPE; k++){
		if(type == k){
			return k;
		}
	}
}

// ======================================
// Bullet
// ======================================


void Bullet::update(float dt) {
	// TODO - update position (using base class), update and check time left to die.
	BaseGameObject::update(dt);
	
}

void Bullet::reset(){
	BaseGameObject::reset();

}

void Ship::shootBullet(){
	
	firingTime = SHIP_FIRE_DELAY;
	Bullet & bullet = bullets.allocate();	//allocate a space for a new bullet
	bullet.reset();
	bullet.position = position;
	bullet.velocity = Vector2f(cos(degToRad(angle)),sin(degToRad(angle)));
	bullet.angle = angle;
			
}

//Need a delay so that bullets dont fire multiple at a time
bool Ship::checkCanFire(){
	return (shoot && firingTime <= 0 ); //Allowed fire,space pressed,time to fire a valid num
}	

// ======================================
// Asteroid
// ======================================

void Asteroid::reset() {
	BaseGameObject::reset();

	spawn_protection = 1.0f;		//Temporary invincibility
	invincible = true;

	float vertexAngle = 360 / ASTEROID_GRANULARITY;
	// TODO - create random asteroid as outlined in class
	for(int k = 0; k < ASTEROID_GRANULARITY; ++k){
		float randomPoint = randomFloat(ASTEROID_MIN_RADIUS,ASTEROID_MAX_RADIUS);
		vertexAngle += ((360/ASTEROID_GRANULARITY) + randomFloat(-1,1) * ASTEROID_ANGLE_VARABILITY);
		angles[k] = vertexAngle;
		vertices[k].x = randomPoint * cos(vertexAngle);
		vertices[k].y = randomPoint * sin(vertexAngle);
	}
	// TODO - random rotation angle 
	angularVelocity = randomFloat(-100,100);
	
	//set enum index
	enumIndex = getEnumIndex();
	size = sizes[enumIndex];

	angle = randomFloat(1,360);
	
	//random velocity derived from angle
	velocity = Vector2f(cos(degToRad(angle)),sin(degToRad(angle))).normal() * randomFloat(ASTEROID_MIN_SPEED,ASTEROID_MAX_SPEED);

}

void Asteroid::update(float dt) {
	BaseGameObject::update(dt);

	//Give asteroid temp spawn protection
	if (spawn_protection <= 0){
		invincible = false;
	}
	else spawn_protection -= dt;
	

	wrap();
	
}

int Asteroid::getEnumIndex(){
	for(int k = 0; k < MAX_ENUM_TYPE; k++){
		if(type == k){
			return k;
		}
	}
}

void Asteroid::wrap(){
	BaseGameObject::wrap();
}
