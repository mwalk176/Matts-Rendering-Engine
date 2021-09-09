#include "Renderer.h"


Renderer::Renderer() {
	integrator = new MDebug();
	maxSamples = 1;

}

Renderer::Renderer(std::string algorithm) {
	std::cout << "Renderer initialized using integrator " << algorithm << std::endl;
	maxSamples = 1;
	if (algorithm == "MDEBUG") {
		integrator = new MDebug();
	} else if (algorithm == "MRAYTRACER") {
		integrator = new MRayTracer();
	}
	else {
		integrator = new MDebug();
	}
	
}

Renderer::~Renderer() {
}

void Renderer::renderScene(Scene& scene, Image& image) {
	
	
	
	//get image dimensions
	int rows = image.getHeight();
	//int columns = image.getWidth();


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
}

void Renderer::renderRow(Scene& scene, Image& image, int y) {
	
	//get camera from scene
	Camera* camera = scene.getCamera();
	Ray primRay = camera->convertToWorld(0, y);

	int columns = image.getWidth();

	for (int x = 0; x < columns; x++) { //TODO implement subpixel tracing

		if(x==0) std::cout << "x = " << x << ", y = " << y << ", primRay = " << primRay << std::endl;
		
		Vec3 col = integrator->render(primRay, scene);


		image.set(x, y, col);

		primRay.d = primRay.d + camera->getIncX(); //move to the right
	}

}
