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
}

void BaseGameObject::reset() {
	state = BaseGameObject::ALIVE;
	velocity = Vector2f::ZERO;
	position = Vector2f::ZERO;
	acceleration = Vector2f::ZERO;
	angle = 0;
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
	
	timeToFire = 0;
	
	health = 100;
	bulletsRemaining = 20;
}

void Ship::update(float dt) {
	// TODO - update position (using base class)
	BaseGameObject::update(dt);
	
	// TODO - process ship control events (update velocity)
	
	// TODO - process fire events 
	if(fire && timeToFire <= 0 && bulletsRemaining > 0){
		timeToFire = SHIP_FIRE_DELAY;
		bulletsRemaining--;
		
		Bullet & bullet = bullets.allocate();
		bullet.reset();
		bullet.position = position;
		bullet.velocity = Vector2f(cos(degToRad(angle)),sin(degToRad(angle)));
		bullet.angle = angle;
	}else{       
		timeToFire -= dt;
	}
	
	//see if need to wrap game object
	if(position.x > ASPECT)position.x = 0.1;
	else if(position.x < 0) position.x = ASPECT - 0.1;
	else if(position.y > 1)position.y = 0.1;
	else if(position.y < 0)position.y = 0.9;
}

// ======================================
// Bullet
// ======================================

void Bullet::reset() {
	// TODO - reset start (using base class),  and reset time left to die.
	BaseGameObject::reset();
	
	timeToDie = BULLET_DIE_DELAY;
}

void Bullet::update(float dt) {
	// TODO - update position (using base class), update and check time left to die.
	BaseGameObject::update(dt);
	
}

// ======================================
// Asteroid
// ======================================

void Asteroid::reset() {
	BaseGameObject::reset();

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
}

void Asteroid::update(float dt) {
	BaseGameObject::update(dt);
	
}

int Asteroid::getEnumIndex(){
	for(int k = 0; k < MAX_ENUM_TYPE; k++)if(type == k){return k;}
}

