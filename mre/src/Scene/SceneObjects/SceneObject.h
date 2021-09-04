#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "../../Utils/Vec3.h"

class SceneObject {
public:
	virtual Vec3 getPos() = 0;
	virtual bool intersect() = 0;

	virtual std::string toString() = 0;
	//virtual friend std::ostream& operator<<(std::ostream& os, SceneObject const& s) = 0;

private:

};



#endif