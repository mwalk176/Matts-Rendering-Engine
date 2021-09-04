#ifndef RENDERER_H
#define RENDERER_H

#include "../Scene/Scene.h"
#include "../Image/Image.h"
#include "Integrator.h"
#include "MDebug.h"
#include "MRayTracer.h"

#include <future>

class Renderer {
public:
	Renderer();
	Renderer(std::string algorithm);
	~Renderer();

	void renderScene(Scene scene, Image& image);
	void renderRow(Scene scene, Image& image, int y);

private:
	Integrator* integrator;
	//enum integratorTypes {MDEBUG, MRAYTRACER, MPATHTRACER};
	int maxSamples;
	bool useMultithreading = false;




};


#endif