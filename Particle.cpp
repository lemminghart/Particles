#include "../Particle.h"
#include <glm\gtc\matrix_transform.hpp>

Particle::Particle() {
	//setup the initial parameters (position)
	currentPos.x = 0.f;
	currentPos.y = 5.f;
	currentPos.z = 0.f;

	//setup the initial speed
	currentV.x = ((float)rand() / RAND_MAX) * 10.f - 5.f;
	currentV.y = ((float)rand() / RAND_MAX) * 10.f - 5.f;
	currentV.z = ((float)rand() / RAND_MAX) * 10.f - 5.f;

	lastPos.x = currentPos.x - currentV.x * (1.f / 30.f);
	lastPos.y = currentPos.y - currentV.y * (1.f / 30.f);
	lastPos.z = currentPos.z - currentV.z * (1.f / 30.f);

	lastV.x = currentV.x;
	lastV.y = currentV.y;
	lastV.z = currentV.z;

	//setup the life time of the particle
	lifeTime = 5;
}

Particle::~Particle() {

}