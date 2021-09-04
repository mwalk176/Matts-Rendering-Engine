#include "Renderer.h"


Renderer::Renderer() {
}

Renderer::Renderer(std::string algorithm) {
	std::cout << "Renderer initialized using integrator " << algorithm << std::endl;
	if (algorithm == "MDEBUG") {
		integrator = new MDebug();
	}
}

Renderer::~Renderer() {
}

void Renderer::renderScene(Scene& scene, Image& image) {
	
	//get camera from scene
	Camera camera = scene.getCamera();
	
	//get image dimensions
	int rows = image.getHeight();
	int columns = image.getWidth();


	for (int y = 0; y < rows; y++) {
		if (useMultithreading) {
			//
			////set up threads and get cores
			//unsigned int numCores = std::thread::hardware_concurrency();
			//std::vector<std::thread> threadList;
			//unsigned int coreCount = 0;
			//
			////create thread for the row
			//threadList.push_back(std::thread(renderRow, scene, std::ref(image), y));
			//
			////if there's max threads for cpu cores, wait until they're done before adding more
			//coreCount++;
			//if (coreCount % numCores == 0) {
			//	for (int i = 0; i < threadList.size(); i++) {
			//		threadList.at(i).join();
			//	}
			//	threadList.clear();
			//}
			renderRow(scene, image, y);

		} else {

			renderRow(scene, image, y);
		}
	}


	


	


	std::cout << "RENDER HERE" << std::endl;
	image.set(42, 492, Vec3(0, 1.0, 1.0));
}

void Renderer::renderRow(Scene& scene, Image& image, int y) {

}
