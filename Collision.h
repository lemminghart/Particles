#pragma once
#include "../Particle.h"

//calcula la d del plano
static float Calculate_d(Coord n, Coord plane_point) {
	//d = -n·P donde P es un punto del plano
	return ((-n.x * plane_point.x) + (-n.y * plane_point.y) + (-n.z * plane_point.z));
}

//calcula la Velocidad normal en un rebote (para aplicar la friccion)
static Coord Calculate_V_Normal(Coord n, Particle *part) {
	Coord Vn;
	Vn.x = ((n.x * part->currentV.x) + (n.y * part->currentV.y) + (n.z * part->currentV.z)) * n.x;
	Vn.y = ((n.x * part->currentV.x) + (n.y * part->currentV.y) + (n.z * part->currentV.z)) * n.y;
	Vn.z = ((n.x * part->currentV.x) + (n.y * part->currentV.y) + (n.z * part->currentV.z)) * n.z;

	return Vn;
}

//calcula la Velocidad tangencial en un rebote (para aplicar la friccion)
static Coord Calculate_V_Tangential(Coord n, Particle *part) {
	Coord Vt;
	Vt.x = part->currentV.x - Calculate_V_Normal(n, part).x;
	Vt.y = part->currentV.x - Calculate_V_Normal(n, part).y;
	Vt.z = part->currentV.x - Calculate_V_Normal(n, part).z;

	return Vt;
}

//Calcula la colisión de una particula con el plano
static void Calculate_Plane_Collision(Coord n, Particle *part, float d) {
	//Coeficiente de elasticidad
	float E = 0.6f;

	//Coeficiente de friccion
	float F = 0.5f;

	//Calculate new position of the particle
	part->currentPos.x = part->currentPos.x - (((1 + E) * ((n.x * part->currentPos.x) + (n.y * part->currentPos.y) + (n.z * part->currentPos.z)) + d) * n.x);
	part->currentPos.y = part->currentPos.y - (((1 + E) * ((n.x * part->currentPos.x) + (n.y * part->currentPos.y) + (n.z * part->currentPos.z)) + d) * n.y);
	part->currentPos.z = part->currentPos.z - (((1 + E) * ((n.x * part->currentPos.x) + (n.y * part->currentPos.y) + (n.z * part->currentPos.z)) + d) * n.z);

	//Calculate new velocity of the particle
	part->currentV.x = part->currentV.x - ((1 + E) * ((n.x * part->currentV.x) + (n.y * part->currentV.y) + (n.z * part->currentV.z)) * n.x);
	part->currentV.y = part->currentV.y - ((1 + E) * ((n.x * part->currentV.x) + (n.y * part->currentV.y) + (n.z * part->currentV.z)) * n.y);
	part->currentV.z = part->currentV.z - ((1 + E) * ((n.x * part->currentV.x) + (n.y * part->currentV.y) + (n.z * part->currentV.z)) * n.z);

	//apply friction
	part->currentV.x = part->currentV.x - F * Calculate_V_Tangential(n, part).x;
	part->currentV.y = part->currentV.y - F * Calculate_V_Tangential(n, part).y;
	part->currentV.z = part->currentV.z - F * Calculate_V_Tangential(n, part).z;
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

	//He cogido los 2 extremos del cubo:
	// {-5,0,-5} : p_bottom, p_left & p_back
	// {5,10,5} : p_front, p_right & p_top
	//las normales apuntan al centro del cubo

	//Collision with plane_bottom
	n = { 0.f,1.f,0.f };
	p = { -5.f,0.f,-5.f };
	if (Check_Plane_Collision(n, part, Calculate_d(n, p))) {
		Calculate_Plane_Collision(n, part, Calculate_d(n, p));
	}

	//Collision with plane_left
	 n = { 1.f,0.f,0.f };
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

	//Collision with plane_front
	n = { 0.f,0.f,-1.f };
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

	//Collision with plane_top
	 n = { 0.f,-1.f,0.f };
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




