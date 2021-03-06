#pragma once
#include "../Particle.h"
#include <cmath>

#define GRAVITY -9.81

enum SOLVER {EULER = 0, VERLET = 1};

static void Euler_Solver(Particle *part, float dt) {
	//set the current position & speed as the last
	part->lastPos = part->currentPos;
	part->lastV = part->currentV;

	//Calculate the new position
	// P = P. + dt * V.
	part->currentPos.x = part->currentPos.x + (dt * part->currentV.x);
	part->currentPos.y = part->currentPos.y + (dt * part->currentV.y);
	part->currentPos.z = part->currentPos.z + (dt * part->currentV.z);

	//funcion calcular fuerzas

	//Calculate the new velocity
	// V = V. + dt * (F/m)[acceleration]
	//We only need to recalculate the V on Y, it's the only one affected by external force
	part->currentV.y = part->currentV.y + (dt * GRAVITY);
}

static void Verlet_Solver(Particle *part, float dt) {
	//set the current position & speed as the last
	glm::vec3 tmp = part->currentPos;
	part->lastV = part->currentV;

	//Calculate the new position
	// P = P + (P - P.) + F/m * dt^2
	//Notice only the Y has external force, the other ones F/m = 0
	part->currentPos.x = part->currentPos.x + (part->currentPos.x - part->lastPos.x);
	part->currentPos.y = part->currentPos.y + (part->currentPos.y - part->lastPos.y) + (GRAVITY * pow(dt, 2));
	part->currentPos.z = part->currentPos.z + (part->currentPos.z - part->lastPos.z);

	part->lastPos = tmp;

	//Calculate velocity
	//  V = (X_t+1 - X_t) / dt
	part->currentV.x = (part->currentPos.x - part->lastPos.x) / dt;
	part->currentV.y = (part->currentPos.y - part->lastPos.y) / dt;
	part->currentV.z = (part->currentPos.z - part->lastPos.z) / dt;
}