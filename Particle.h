#pragma once
#include <vector>

struct Coord {
	float x, y, z;
};

class Particle {
public:
	Coord currentPos, lastPos; //Stores Current and Last Position
	Coord currentV, lastV; //Stores Current and Last Velocity
	float lifeTime; //Life time of the particle

	Particle();
	~Particle();
};

static std::vector <Particle> partArray; //vector de particulas