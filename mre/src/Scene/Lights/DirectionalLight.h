#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight : public Light {
public:
	DirectionalLight();
	DirectionalLight(Vec3 d);

	Vec3 getLightDirection();

	std::string toString();

private:
	Vec3 lightDirection;
};



#endif
