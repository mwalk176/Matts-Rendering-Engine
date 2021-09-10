#ifndef MDEBUGMAT_H
#define MDEBUGMAT_H

#include "Material.h"

class MDebugMat : public Material {
public:
	MDebugMat(Vec3 c);

	Vec3 getColor();

	std::string toString();


private:
	Vec3 color;


};




#endif
