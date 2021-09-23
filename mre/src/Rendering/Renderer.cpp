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

	time_t timer;
	double startTime = time(&timer);
	double deltaTime = -1;
	bool calculateTime = false;
	double averageCycleTime = 0;
	double totalTime = 0;


	for (int y = 0; y < rows; y++) {
		

		if (calculateTime) {
			deltaTime = time(&timer) - startTime;
			startTime = time(&timer);
			averageCycleTime = averageCycleTime == 0 ? (averageCycleTime + deltaTime) : (averageCycleTime + deltaTime) / 2.0;
			totalTime = totalTime + deltaTime;
			calculateTime = false;
			std::cout << "Cycle complete, current y: " << y << std::endl;
			std::cout << "  Elapsed time: " << (int)(totalTime / 60) << " minutes, " << (int)totalTime % 60 << " seconds" << std::endl;
			std::cout << "  Previous cycle took " << deltaTime << " seconds to complete" << std::endl;
			std::cout << "  Average cycle time: " << averageCycleTime << " seconds" << std::endl;
			int remainingRows = rows - y;
			double remainingCycles = remainingRows / numCores;
			double estimatedTime = remainingCycles * averageCycleTime;
			int minutesLeft = estimatedTime / 60;
			int secondsLeft = (int)estimatedTime % 60;
			std::cout << "  " << remainingCycles << " cycles left" << std::endl;
			std::cout << "  Estimated time remaining: " << minutesLeft << " minutes, " << secondsLeft << " seconds" << std::endl << std::endl;

		}



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
				calculateTime = true;
			}
		} else {
			std::cout << "y: " << y << std::endl;
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
						//float rX = -0.25;
											//float rY = -0.25;

						float rX = ((float)rand() / RAND_MAX) / -2.0;
						float rY = ((float)rand() / RAND_MAX) / -2.0;
						//float rX = (rand() / RAND_MAX);
						//float rY = rand();
						if (subX == 1) rX += 0.5;
						if (subY == 1) rY += 0.5;


						float xAdjusted = x + rX;
						float yAdjusted = y + rY;

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