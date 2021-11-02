#ifndef ACCELSTRUCTURE_H
#define ACCELSTRUCTURE_H


#include "../../Utils/Vec3.h"
#include "../SceneObjects/SceneObject.h"
//#include <vector>


class AccelStructure {
public:
	virtual void buildTree(std::vector<SceneObject*> objects) = 0;
	virtual SceneObject* traverseTree(Ray r, float& closestPoint) = 0;
	virtual bool findFirstIntersection(Ray r, float& lightDist) = 0;
	
protected:

private:

};







#endif
