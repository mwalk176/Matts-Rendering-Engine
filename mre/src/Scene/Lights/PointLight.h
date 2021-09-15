#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class PointLight : public Light {
public:
	PointLight();
	PointLight(Vec3 p);

	Vec3 getPos();

	std::string toString();

};



#endif
