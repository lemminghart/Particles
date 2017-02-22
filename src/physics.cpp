#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>

#include "../Particle.h"

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



}
void PhysicsUpdate(float dt) { //calcular las affeciones sobre las particulas
	//TODO
	//pasar update particles al final de aqui -> LilSpheres::updateParticles(0, LilSpheres::maxParticles, partVerts);
}
void PhysicsCleanup() { //hacer delete de todos los new, etc
	//TODO
}