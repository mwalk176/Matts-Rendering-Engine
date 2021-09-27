#ifndef MATERIAL_H
#define MATERIAL_H


#include "../Utils/Vec3.h"

class Material {
public:
	virtual std::string toString() = 0;
	int matType = -1; //-1 no material type, 0 MDEBUGMAT, 1 MRAYTRACERMAT, 2 MPATHTRACERMAT

protected:


private:

};




#endif