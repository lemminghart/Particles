#include "../Particle.h"
#include <glm\gtc\matrix_transform.hpp>

Particle::Particle() {
	//setup the initial parameters (position)
	currentPos.x = 0;
	currentPos.y = 5;
	currentPos.z = 0;

	lastPos.x = (((float)rand() / RAND_MAX) * 10.f - 5.f) * (1 / 30);
	lastPos.y = (((float)rand() / RAND_MAX) * 10.f - 5.f) * (1 / 30);
	lastPos.z = (((float)rand() / RAND_MAX) *  10.f - 5.f) * (1 / 30);

	//setup the initial speed
	currentV.x = ((float)rand() / RAND_MAX) * 10.f - 5.f;
	currentV.y = ((float)rand() / RAND_MAX) * 10.f - 5.f;
	currentV.z = ((float)rand() / RAND_MAX) * 10.f - 5.f;

	lastV.x = currentV.x;
	lastV.y = currentV.y;
	lastV.z = currentV.z;

	//setup the life time of the particle
	lifeTime = 5;
}

Particle::~Particle() {

}