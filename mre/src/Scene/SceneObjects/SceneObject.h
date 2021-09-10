#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "../../Utils/Vec3.h"
#include "../../Utils/Ray.h"
#include "../../Materials/Material.h"
#include "../../Materials/MDebugMat.h"
#include <vector>

class SceneObject {
public:
	Vec3 getPos();
	virtual bool intersect(Ray r, double& p0, double& p1) = 0;

	std::vector<Material*> getMaterials();

	virtual std::string toString() = 0;
	//virtual friend std::ostream& operator<<(std::ostream& os, SceneObject const& s) = 0;

protected:
	Vec3 pos;
	std::vector<Material*> materials;

private:

};



#endif