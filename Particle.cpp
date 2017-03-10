#include "../Particle.h"
#include <glm\gtc\matrix_transform.hpp>

Particle::Particle() {
	//setup the life time of the particle
	lifeTime = 3;
	alive = false;

	if (emitter == WATERFALL) {
		currentPos.x = ((float)rand() / RAND_MAX) * 10.f - 5.f;
		currentPos.y = 9.9f;
		currentPos.z = ((float)rand() / RAND_MAX) * 2.f - 1.f;

		currentV.x = 0;
		currentV.y = 0;
		currentV.z = 0;

		lastPos.x = currentPos.x;
		lastPos.y = currentPos.y;
		lastPos.z = currentPos.z;

		lastV.x = currentV.x;
		lastV.y = currentV.y;
		lastV.z = currentV.z;
	}
	else if (emitter == FOUNTAIN) {
		currentPos.x = 0.f;
		currentPos.y = 3.f;
		currentPos.z = 0.f;

		currentV.x = ((float)rand() / RAND_MAX) * 10.f - 5.f;
		currentV.y = ((float)rand() / RAND_MAX) * 3.f + 8.1f;
		currentV.z = ((float)rand() / RAND_MAX) * 10.f - 5.f;

		lastPos.x = currentPos.x - currentV.x * (1.f / 30.f);
		lastPos.y = currentPos.y - currentV.y * (1.f / 30.f);
		lastPos.z = currentPos.z - currentV.z * (1.f / 30.f);

		lastV.x = currentV.x;
		lastV.y = currentV.y;
		lastV.z = currentV.z;
	}
	if (emitter == BASIC) {
		//Basic initialization

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

	}
}

Particle::~Particle() {

}