#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "Image.h"
#include "Integrator.h"

class Renderer {
public:
	Renderer();
	Renderer(std::string algorithm);
	~Renderer();

	void renderScene(Scene& scene, Image& image);

private:
	Integrator* integrator;




};


#endif