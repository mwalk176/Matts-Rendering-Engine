#include "BoundingBox.h"

BoundingBox::BoundingBox(SceneObject* o) {
    obj = o;
    min = Vec3();
    max = Vec3();
    o->getBounds(min, max);
    bounds[0] = min;
    bounds[1] = max;
}

bool BoundingBox::intersect(Ray& r) {

    //largely inspired and taken from ScratchaPixel's method on ray box intersections
    //https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
    float tx0, tx1, ty0, ty1, tz0, tz1;

    tx0 = (bounds[r.sign[0]].x - r.o.x) * r.inv.x;
    tx1 = (bounds[1 - r.sign[0]].x - r.o.x) * r.inv.x;
    ty0 = (bounds[r.sign[1]].y - r.o.y) * r.inv.y;
    ty1 = (bounds[1 - r.sign[1]].y - r.o.y) * r.inv.y;

    if (tx0 > ty1 || ty0 > tx1) return false;
    if (ty0 > tx0) tx0 = ty0;
    if (ty1 < tx1) tx1 = ty1;

    tz0 = (bounds[r.sign[2]].z - r.o.z) * r.inv.z;
    tz1 = (bounds[1 - r.sign[2]].z - r.o.z) * r.inv.z;

    if (tx0 > tz1 || tz0 > tx1) return false;
    if (tz0 > tx0) tx0 = tz0;
    if (tz1 < tx1) tx1 = tz1;

    return true;
}
