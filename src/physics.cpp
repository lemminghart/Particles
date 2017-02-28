#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>

#include <glm\gtc\type_ptr.hpp>


#include "../Particle.h"
#include "../Solvers.h"

namespace LilSpheres {
	extern const int maxParticles;
	extern void setupParticles(int numTotalParticles, float radius = 0.05f);
	extern void cleanupParticles();
	extern void updateParticles(int startIdx, int count, float* array_data);
	extern void drawParticles(int startIdx, int count);
}

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
		partArray[i] = new Particle;
	}



}
void PhysicsUpdate(float dt) { //calcular las afecciones sobre las particulas
	//TODO

	int solver = EULER;

	if (solver == EULER) {
		for (int i = 0; i < SHRT_MAX; i++) {
			Euler_Solver(partArray[i], dt);
		}
	}
	else if (solver == VERLET) {
		for (int i = 0; i < SHRT_MAX; i++) {
			Verlet_Solver(partArray[i], dt);
		}
	}
	else {
		//ERROR
	}

	//cada 3000/33.3 entradas 1 seg

	//pasar update particles al final de aqui -> LilSpheres::updateParticles(0, LilSpheres::maxParticles, partVerts);
	//updatea las particulas
	//LilSpheres::updateParticles(0, SHRT_MAX, partVerts);
	
}
void PhysicsCleanup() { //hacer delete de todos los new, etc
	//TODO
}