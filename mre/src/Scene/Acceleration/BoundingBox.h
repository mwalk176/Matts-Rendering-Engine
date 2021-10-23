#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H


#include "../SceneObjects/SceneObject.h"


class BoundingBox {
public:
	BoundingBox(SceneObject* o);
	bool intersect(Ray& r);

	SceneObject* obj;


	friend std::ostream& operator<<(std::ostream& os, BoundingBox const& b);

private:

	void computeCenter();

	
	std::vector<BoundingBox*> children;
	

	Vec3 min;
	Vec3 max;
	Vec3 bounds[2];
	Vec3 center;


};






#endif

