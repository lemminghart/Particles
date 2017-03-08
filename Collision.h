#pragma once
#include "../Particle.h"

//calcula la d del plano
static float Calculate_d(Coord n, Coord plane_point) {
	//d = -n·P donde P es un punto del plano
	return ((-n.x * plane_point.x) + (-n.y * plane_point.y) + (-n.z * plane_point.z));
}

//calcula la Velocidad normal en un rebote (para aplicar la friccion)
static Coord Calculate_V_Normal(Coord n, Coord v) {
	Coord Vn; //normal vector

	//v may be the Particle velocity (EULER) or the Lastpos->CurrentPos vector in VERLET

	//Vn = (V·n) * n
	Vn.x = ((n.x * v.x) + (n.y * v.y) + (n.z * v.z)) * n.x;
	Vn.y = ((n.x * v.x) + (n.y * v.y) + (n.z * v.z)) * n.y;
	Vn.z = ((n.x * v.x) + (n.y * v.y) + (n.z * v.z)) * n.z;

	return Vn;
}

//calcula la Velocidad tangencial en un rebote (para aplicar la friccion)
static Coord Calculate_V_Tangential(Coord n, Coord v) {
	Coord Vt; //tangential vector

	//v may be the Particle velocity (EULER) or the Lastpos->CurrentPos vector in VERLET

	//Vt = V - Vn
	Vt.x = v.x - Calculate_V_Normal(n, v).x;
	Vt.y = v.y - Calculate_V_Normal(n, v).y;
	Vt.z = v.z - Calculate_V_Normal(n, v).z;

	return Vt;
}

//Calcula la colisión de una particula con el plano
static void Calculate_Plane_Collision(Coord n, Particle *part, float d, int solver) {
	//Coeficiente de elasticidad
	float E = 0.7f;

	//Coeficiente de friccion
	float F = 0.3f;

	//Calculate new position of the particle
	part->currentPos.x = part->currentPos.x - ((1 + E) * (((n.x * part->currentPos.x) + (n.y * part->currentPos.y) + (n.z * part->currentPos.z)) + d) * n.x);
	part->currentPos.y = part->currentPos.y - ((1 + E) * (((n.x * part->currentPos.x) + (n.y * part->currentPos.y) + (n.z * part->currentPos.z)) + d) * n.y);
	part->currentPos.z = part->currentPos.z - ((1 + E) * (((n.x * part->currentPos.x) + (n.y * part->currentPos.y) + (n.z * part->currentPos.z)) + d) * n.z);

	
	if (solver == EULER) {
		//Calculate new velocity of the particle
		part->currentV.x = part->currentV.x - ((1 + E) * ((n.x * part->currentV.x) + (n.y * part->currentV.y) + (n.z * part->currentV.z)) * n.x);
		part->currentV.y = part->currentV.y - ((1 + E) * ((n.x * part->currentV.x) + (n.y * part->currentV.y) + (n.z * part->currentV.z)) * n.y);
		part->currentV.z = part->currentV.z - ((1 + E) * ((n.x * part->currentV.x) + (n.y * part->currentV.y) + (n.z * part->currentV.z)) * n.z);

		//apply friction on EULER
		part->currentV.x = part->currentV.x - F * Calculate_V_Tangential(n, part->currentV).x;
		part->currentV.y = part->currentV.y - F * Calculate_V_Tangential(n, part->currentV).y;
		part->currentV.z = part->currentV.z - F * Calculate_V_Tangential(n, part->currentV).z;
	}
	if (solver == VERLET) {
		//Mirroring the last pos, so we can calculate new direction properly
		// P = P' - 2(n·P' + d) · n
		part->lastPos.x = part->lastPos.x - ((1 + E) * ((n.x * part->lastPos.x) + (n.y * part->lastPos.y) + (n.z * part->lastPos.z) + d) * n.x);
		part->lastPos.y = part->lastPos.y - ((1 + E) * ((n.x * part->lastPos.x) + (n.y * part->lastPos.y) + (n.z * part->lastPos.z) + d) * n.y);
		part->lastPos.z = part->lastPos.z - ((1 + E)* ((n.x * part->lastPos.x) + (n.y * part->lastPos.y) + (n.z * part->lastPos.z) + d) * n.z);

		//apply Friction and elasticity
		float alpha = 1 - E; //elasticity
		//friction uses the raw variable F of friction

		//previoulsy we calculate the vector between lastPos & currentPos to calculate Normal & Tangential vectors
		Coord vector;
		vector.x = part->currentPos.x - part->lastPos.x;
		vector.y = part->currentPos.y - part->lastPos.y;
		vector.z = part->currentPos.z - part->lastPos.z;

		// P = P + alpha * Vn + F * Vt
		part->lastPos.x = part->lastPos.x + (alpha * Calculate_V_Normal(n, vector).x) + (F * Calculate_V_Tangential(n, vector).x);
		part->lastPos.y = part->lastPos.y + (alpha * Calculate_V_Normal(n, vector).y) + (F * Calculate_V_Tangential(n, vector).y);
		part->lastPos.z = part->lastPos.z + (alpha * Calculate_V_Normal(n, vector).z) + (F * Calculate_V_Tangential(n, vector).z);
	}
}

//bool que calcula si hay colision con un plano donde n = normal del plano, part = Particula y d = un punto del plano
static bool Check_Plane_Collision(Coord n, Particle *part, float d) {

	//collision = true if ((n·p_t + d)(n·p'_t + d) <= 0)
	float check = (((n.x * part->lastPos.x) + (n.y * part->lastPos.y) + (n.z * part->lastPos.z)) + d) *
		(((n.x * part->currentPos.x) + (n.y * part->currentPos.y) + (n.z * part->currentPos.z)) + d);

	if (check <= 0) {
		return true;
	}
	else {
		return false;
	}
}

//Calcula la colision con la caja contenedora
static void Box_Collision(Particle *part, int solver) {
	Coord n;
	Coord p;

	//He cogido los 2 extremos del cubo:
	// {-5,0,-5} : p_bottom, p_left & p_back
	// {5,10,5} : p_front, p_right & p_top
	//las normales apuntan al centro del cubo

	//Collision with plane_bottom
	n = { 0.f,1.f,0.f };
	p = { -5.f,0.f,-5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p), solver);
	}

	//Collision with plane_left
	 n = { 1.f,0.f,0.f };
	 p = { -5.f,0.f,-5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p), solver);
	}

	//Collision with plane_back
	 n = { 0.f,0.f,1.f };
	 p = { -5.f,0.f,-5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p), solver);
	}

	//Collision with plane_front
	n = { 0.f,0.f,-1.f };
	p = { 5.f,10.f,5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p), solver);
	}

	//Collision with plane_right
	n = { -1.f,0.f,0.f };
	p = { 5.f,10.f,5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p), solver);
	}

	//Collision with plane_top
	 n = { 0.f,-1.f,0.f };
	 p = { 5.f,10.f,5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p), solver);
	}	
}

//Calcula TODAS las colisiones del programa
static void Collision_Manager(Particle *part, int solver) {
	
	//Check collision with BOX
	Box_Collision(part, solver);
}




