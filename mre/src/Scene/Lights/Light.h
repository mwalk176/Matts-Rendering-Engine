#ifndef LIGHT_H
#define LIGHT_H

#include "../../Utils/Vec3.h"

class Light {
public:
	Light();
	Vec3 getPos();

	virtual std::string toString() = 0;

protected:
	Vec3 pos;
};


#endif