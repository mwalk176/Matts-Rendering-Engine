#include <iostream>

#include "Image.h"
#include "Scene.h"
#include "Renderer.h"



int main(int argc, char* argv[]) {
	//std::cout << "Hello World!" << std::endl;

	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	std::string sceneFile = argv[3];



	//get scene
	Scene scene(sceneFile);

	//render scene
	//Image output = new Image(1920, 1080) **USE COMMAND LINE ARGS**
	Image output(width, height);
	Vec3 hi(0.2, 0.8, 1.0);
	output.set(24, 42, hi);
	Vec3 test = output.get(24, 42);
	std::cout << test << std::endl;

	Renderer renderer("path tracer"); //  **COMMAND LINE ARGS**) renderer is real class, make abstract render algorirthm for ray tracer and path tracer
	renderer.renderScene(scene, output); // *pass output by reference so it modifies output
	//output image
	
	//write to ppm file
	output.writeToPPMFile();

	return 0;
}