#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H


#include "../SceneObjects/SceneObject.h"


class BoundingBox {
public:
	BoundingBox(SceneObject* o);
	bool intersect(Ray& r);

private:

	SceneObject* obj;
	std::vector<BoundingBox*> children;

	Vec3 min;
	Vec3 max;
	Vec3 bounds[2];


};






#endif

