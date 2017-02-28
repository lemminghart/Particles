#pragma once
#include <vector>

struct Coord {
	float x, y, z;
};

std::vector <Particle *> partArray(SHRT_MAX); //vector de particulas

class Particle {
public:
	Coord currentPos, lastPos; //Stores Current and Last Position
	Coord currentV, lastV; //Stores Current and Last Velocity
	float lifeTime; //Life time of the particle

	Particle();
	~Particle();
};