#include <iostream>

#include "../Image/Image.h"
#include "../Scene/Scene.h"
#include "../Rendering/Renderer.h"



int main(int argc, char* argv[]) {
	std::cout << "Hello World!" << std::endl;

	if (argc < 2) {
		std::cout << "Error: please specify a width, height, a scenefile, and integrator" << std::endl;
		return 0;
	}

	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	std::string sceneFile = argv[3];
	std::string integrator = argv[4];



	//get scene
	Scene scene(sceneFile);

	//render scene
	//Image output = new Image(1920, 1080) **USE COMMAND LINE ARGS**
	Image output(width, height);
	Vec3 hi(0.2, 0.8, 1.0);
	output.set(24, 42, hi);
	Vec3 test = output.get(24, 42);
	std::cout << test << std::endl;

	Renderer renderer(integrator); //  **COMMAND LINE ARGS**) renderer is real class, make abstract render algorirthm for ray tracer and path tracer
	renderer.renderScene(scene, output); // *pass output by reference so it modifies output
	//output image
	
	//write to ppm file
	output.writeToPPMFile();

	return 0;
}