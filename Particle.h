#pragma once
#include <vector>

struct Coord { float x, y, z; };

enum Type {WATERFALL = 0, FOUNTAIN = 1, BASIC = 2};

class Particle {
public:
	Coord currentPos, lastPos; //Stores Current and Last Position
	Coord currentV, lastV; //Stores Current and Last Velocity
	float lifeTime; //Life time of the particle
	Type emitter = FOUNTAIN; //type of initialization
	bool alive;

	Particle();
	~Particle();
};

static std::vector <Particle> partArray; //vector de particulas