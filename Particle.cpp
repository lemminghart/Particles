#include "../Particle.h"
#include <glm\gtc\matrix_transform.hpp>

Particle::Particle() {
	//setup the initial parameters (position)
	currentPos.x = 0;
	currentPos.y = 0;
	currentPos.z = 0;

	//setup the initial speed
	currentV.x = ((float)rand() / RAND_MAX) * 10.f - 5.f;
	currentV.y = ((float)rand() / RAND_MAX) * 10.f - 5.f;
	currentV.z = ((float)rand() / RAND_MAX) * 10.f - 5.f;

	//setup the life time of the particle
	lifeTime = 5;
}

Particle::~Particle() {

}