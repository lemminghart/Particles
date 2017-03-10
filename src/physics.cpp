#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <iostream>

#include <glm\gtc\type_ptr.hpp>

#include "../Particle.h"
#include "../Solvers.h"
#include "../Collision.h"

namespace LilSpheres {
	extern const int maxParticles;
	extern void setupParticles(int numTotalParticles, float radius = 0.05f);
	extern void cleanupParticles();
	extern void updateParticles(int startIdx, int count, float* array_data);
	extern void drawParticles(int startIdx, int count);
}

namespace Utils { //Namespace para manejar variables propias del sistema
	//time
	int time = 0;
	extern float percent = 0.f;
	//particles
	extern int particlesPerSecond = 1000;
	//solver
	extern int solver = VERLET; //CAN BE EULER or VERLET
}

using namespace Utils;

bool show_test_window = false;
void GUI() {
	{	//FrameRate
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		//TODO
	}

	// ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if(show_test_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
}

void PhysicsInit() { //inicializar aqui las particulas
	//TODO
	
	for (int i = 0; i < SHRT_MAX; i++) {
		Particle temp;
		partArray.push_back(temp);
	}



}
void PhysicsUpdate(float dt) { //calcular las afecciones sobre las particulas
	//TODO

	int temp_counter = 0;

	//PhysicsUpdate se llama 10 veces por segundo, y cada vez genera X particulas nuevas
	for (int i = 0; i < SHRT_MAX; i++) {
		if (partArray[i].alive == false && temp_counter < particlesPerSecond/10) {
			partArray[i].~Particle();
			std::cout << "Particle " << i << " DESTROYED" << std::endl;
			partArray[i] = *new Particle;
			partArray[i].alive = true;
			std::cout << "Particle " << i << " CREATED" << std::endl;
			temp_counter++;
		}
	}



	if (solver == EULER) {
		for (int i = 0; i < SHRT_MAX; i++) {
			if (partArray[i].alive) {
				Euler_Solver(&partArray[i], dt);
				Collision_Manager(&partArray[i], solver);
			}
		}
	}
	else if (solver == VERLET) {
		for (int i = 0; i < SHRT_MAX; i++) {
			if (partArray[i].alive) {
				Verlet_Solver(&partArray[i], dt);
				Collision_Manager(&partArray[i], solver);
			}
		}
	}
	else {
		//ERROR
	}

	//cada 3000/33.3 entradas 1 seg

	float *partVerts = new float[SHRT_MAX * 3];
	for (int i = 0; i < SHRT_MAX; ++i) {
		if (partArray[i].alive) {
			partVerts[i * 3 + 0] = partArray[i].currentPos.x;
			partVerts[i * 3 + 1] = partArray[i].currentPos.y;
			partVerts[i * 3 + 2] = partArray[i].currentPos.z;
		}
	}

	//updatea las particulas
	LilSpheres::updateParticles(0, SHRT_MAX, partVerts);
	delete[] partVerts;

	//aqui entra cada 1 segundo
	if (percent > 0.33f) {
		time++;
		std::cout << "TIME:" << time << std::endl;

		//reducimos la vida de las particulas vivas
		for (int i = 0; i < SHRT_MAX; i++) {
			if (partArray[i].alive) {
				partArray[i].lifeTime--;
				//cambiamos el estado de las particulas que hayan muerto
				if (partArray[i].lifeTime <= 0.f) {
					partArray[i].alive = false;
				}
			}
		}
		
		
		//bajamos el contador a 0 para que al segundo vuelva a entrar aqui
		percent = 0;
	}

	percent += dt; //contador incremental
}
void PhysicsCleanup() { //hacer delete de todos los new, etc
	
	//NOT NECESSARY. see PhysicsInit() on this document.
	/*for (int i = 0; i < SHRT_MAX; i++) {
		partArray.pop_back();
	}

	partArray.clear();*/
}