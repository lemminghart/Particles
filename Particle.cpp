#include "../Particle.h"
#include <glm\gtc\matrix_transform.hpp>

Particle::Particle() {
	//setup the initial parameters (position)
	currentPos.x = 0.f;
	currentPos.y = 5.f;
	currentPos.z = 0.f;

	lastPos.x = (((float)rand() / RAND_MAX) * 10.f - 5.f) * (1.f / 30.f);
	lastPos.y = (((float)rand() / RAND_MAX) * 10.f - 5.f) * (1.f / 30.f);
	lastPos.z = (((float)rand() / RAND_MAX) * 10.f - 5.f) * (1.f / 30.f);

	//setup the initial speed
	currentV.x = ((float)rand() / RAND_MAX) * 10.f - 5.f;
	currentV.y = ((float)rand() / RAND_MAX) * 10.f - 5.f;
	currentV.z = ((float)rand() / RAND_MAX) * 10.f - 5.f;

	lastV.x = currentV.x;
	lastV.y = currentV.y;
	lastV.z = currentV.z;

	//setup the life time of the particle
	lifeTime = 5.f;
}

Particle::~Particle() {

}