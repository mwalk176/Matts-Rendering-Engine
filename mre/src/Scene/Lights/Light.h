#ifndef LIGHT_H
#define LIGHT_H

#include "../../Utils/Vec3.h"

class Light {
public:
	Light();
	Vec3 getPos();

	virtual std::string toString() = 0;
	int lightType = -1; //-1 no type set, 0 point light, 1 directional light

protected:
	Vec3 pos;
	Vec3 lightColor;
};


#endif