#ifndef _OBJECT3D_H
#define _OBJECT3D_H
#include"material.h"
#include"ray.h"
#include"hit.h"
class Object3D
{
private:

public:
    Material* _material=nullptr;

    virtual bool intersect(const Ray &r,Hit &h,float tmin)=0;
};


#endif
