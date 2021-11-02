#ifndef RENDERER_H
#define RENDERER_H

#include "../Scene/Scene.h"
#include "../Image/Image.h"
#include "Integrator.h"
#include "MDebug.h"
#include "MRayTracer.h"
#include "MPathTracer.h"
//#include "RenderSettings.h"

#include <future>
#include <cmath>
#include <time.h>

class Renderer {
public:
	//Renderer();
	Renderer(std::string algorithm, Scene* s);
	~Renderer();

	void renderScene(Image& image);
	void renderRow(Image& image, int y);

private:
	Integrator* integrator;
	//enum integratorTypes {MDEBUG, MRAYTRACER, MPATHTRACER};
	//RenderSettings* settings = RenderSettings::getInstance();
	Scene* scene;


	bool useMultithreading = true;

};


#endif