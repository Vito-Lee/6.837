#ifndef _TRANSFORM_H
#define _TRANSFORM_H
#include"object3d.h"
#include"matrix.h"
class Transform:public Object3D
{
private:
    Object3D* _object;
    Matrix _mat,_invMat,_invTpMat;
public:
    Transform(Matrix &m,Object3D* o);
    bool intersect(const Ray &r, Hit &h, float tmin) override;


};



#endif
