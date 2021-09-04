#include "Renderer.h"

Renderer::Renderer() {
}

Renderer::Renderer(std::string algorithm) {
	std::cout << "Renderer initialized" << std::endl;
}

Renderer::~Renderer() {
}

void Renderer::renderScene(Scene& scene, Image& image) {
	std::cout << "RENDER HERE" << std::endl;
	image.set(42, 492, Vec3(0, 1.0, 1.0));
}
