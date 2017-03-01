#pragma once
#include "../Particle.h"

//calculamos la d del plano
static float Calculate_d(Coord n, Coord plane_point) {
	//d = -n·P donde P es un punto del plano
	return ((-n.x * plane_point.x) + (-n.y * plane_point.y) + (-n.z * plane_point.z));
}

//Calcula la colisión de una particula con el plano
static void Calculate_Plane_Collision(Coord n, Particle *part, float d) {
	//Coeficiente de elasticidad
	float E = 0.8f;

	//Coeficiente de friccion
	float F = 0.2f;

	//Calculate new position of the particle
	part->currentPos.x = part->currentPos.x - (((1 + E) * ((n.x * part->currentPos.x) + (n.y * part->currentPos.y) + (n.z * part->currentPos.z)) + d) * n.x);
	part->currentPos.y = part->currentPos.y - (((1 + E) * ((n.x * part->currentPos.x) + (n.y * part->currentPos.y) + (n.z * part->currentPos.z)) + d) * n.y);
	part->currentPos.z = part->currentPos.z - (((1 + E) * ((n.x * part->currentPos.x) + (n.y * part->currentPos.y) + (n.z * part->currentPos.z)) + d) * n.z);

	//Calculate new velocity of the particle

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
static void Box_Collision(Particle *part) {
	Coord n;
	Coord p;


	//Collision with plane_bottom
	n = { 0.f,1.f,0.f };
	p = { -5.f,0.f,-5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p));
	}

	//Collision with plane_left
	 n = { -1.f,0.f,0.f };
	 p = { -5.f,0.f,-5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p));
	}

	//Collision with plane_back
	 n = { 0.f,0.f,1.f };
	 p = { -5.f,0.f,-5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p));
	}

	//Collision with plane_top
	 n = { 0.f,-1.f,0.f };
	 p = { 5.f,10.f,5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p));
	}

	//Collision with plane_right
	 n = { -1.f,0.f,0.f };
	 p = { 5.f,10.f,5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p));
	}

	//Collision with plane_front
	 n = { 0.f,0.f,-1.f };
	 p = { 5.f,10.f,5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p));
	}
}

//Calcula TODAS las colisiones del programa
static void Collision_Manager(Particle *part) {
	
	//Check collision with BOX
	Box_Collision(part);
}




