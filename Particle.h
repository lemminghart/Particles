#pragma once
#include <vector>
#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

enum Type {WATERFALL = 0, FOUNTAIN = 1, BASIC = 2};

class Particle {
public:
	glm::vec3 currentPos, lastPos; //Stores Current and Last Position
	glm::vec3 currentV, lastV; //Stores Current and Last Velocity
	float lifeTime; //Life time of the particle
	Type emitter = WATERFALL; //type of initialization
	bool alive;

	Particle();
	~Particle();
};

static std::vector <Particle> partArray; //vector de particulas