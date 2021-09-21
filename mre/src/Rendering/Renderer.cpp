#include "Renderer.h"


Renderer::Renderer() {
	integrator = new MDebug();

}

Renderer::Renderer(std::string algorithm) {
	std::cout << "Renderer initialized using integrator " << algorithm << std::endl;
	if (algorithm == "MDEBUG") {
		integrator = new MDebug();
	} else if (algorithm == "MRAYTRACER") {
		integrator = new MRayTracer();
	}
	else if (algorithm == "MPATHTRACER") {
		integrator = new MPathTracer();
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

	


	//set up threads and get cores
	unsigned int numCores = std::thread::hardware_concurrency();
	std::vector<std::thread> threadList;
	unsigned int coreCount = 0;


	for (int y = 0; y < rows; y++) {
		std::cout << "y: " << y << std::endl;
		if (useMultithreading) {

			//create thread for the row
			threadList.push_back(std::thread(&Renderer::renderRow, this, std::ref(scene), std::ref(image), y));
			
			//if there's max threads for cpu cores, wait until they're done before adding more
			coreCount++;
			if (coreCount % numCores == 0) {
				for (int i = 0; i < threadList.size(); i++) {
					threadList.at(i).join();
				}
				threadList.clear();
			}
		} else {
			renderRow(scene, image, y);
		}
	}
}

void Renderer::renderRow(Scene& scene, Image& image, int y) {
	
	
	if(useMultithreading) srand(std::hash<std::thread::id>{}(std::this_thread::get_id())); 
	//srand(std::hash<std::thread::id>{}(std::this_thread::get_id()) + currentSamples);
	
	//get camera from scene
	Camera* camera = scene.getCamera();

	Ray primRay = camera->convertToWorld(0, y);
	

	int columns = image.getWidth();
	int subRows = 2;
	int subColumns = 2;

	bool superSample = true;

	//std::cout << "y = " << y << ", primRay = " << primRay << std::endl;

	for (int x = 0; x < columns; x++) {

		Vec3 col = Vec3();
		int timesSampled = 0;
		int maxSamples = 1;

		if (superSample) {
			for (int subY = 0; subY < subRows; subY++) { //calculate subpixel grid
				for (int subX = 0; subX < subColumns; subX++) {
					for (int samples = 0; samples < maxSamples; samples++) {
						//double rX = -0.25;
											//double rY = -0.25;

						double rX = ((double)rand() / RAND_MAX) / -2.0;
						double rY = ((double)rand() / RAND_MAX) / -2.0;
						//double rX = (rand() / RAND_MAX);
						//double rY = rand();
						if (subX == 1) rX += 0.5;
						if (subY == 1) rY += 0.5;


						double xAdjusted = x + rX;
						double yAdjusted = y + rY;

						Ray primRay = camera->convertToWorld(xAdjusted, yAdjusted);

						

						col = col + integrator->render(primRay, scene);
						timesSampled++;
					}

					
					
					


					
				}
			}
			col = col / timesSampled;
			col.clamp();
			image.set(x, y, col);

		} else {
			//if (x == 0) std::cout << "x = " << x << ", y = " << y << ", primRay = " << primRay << std::endl;

			Vec3 col = integrator->render(primRay, scene);


			image.set(x, y, col);
			primRay.d = primRay.d + camera->getIncX(); //move to the right
		}
		

		
	}

}