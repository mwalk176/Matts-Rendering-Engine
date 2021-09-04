#ifndef LIGHT_H
#define LIGHT_H

#include "../../Utils/Vec3.h"

class Light {
public:
	virtual Vec3 pos() = 0;

};


#endif