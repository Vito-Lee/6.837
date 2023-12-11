#ifndef _TRIANGLE_H
#define _TRIANGLE_H
#include "object3d.h"
#include "plane.h"
#include "material.h"
#include "vectors.h"

class Triangle : public Object3D {
    Vec3f _v0, _v1, _v2, _norm;
    Plane _plane;

public:
    Triangle(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2, Material *m);

    bool intersect(const Ray &r, Hit &h, float tmin) override;
};


#endif
