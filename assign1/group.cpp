#include"group.h"
#include<assert.h>
#include<limits>
void Group::addObject(int index,Object3D* obj){
    assert(index<_nobjects);
    objs[index]=obj;
}
Group::Group(int n){
    assert(n>=0);
    _nobjects=n;
    objs.resize(n);
}
bool Group::intersect(const Ray &r,Hit &h,float tmin){
    //group的相交方法是为了找出最小t值的object3d
    h=Hit(std::numeric_limits<float>::max(),nullptr);
    bool success=false;
    for(auto obj:objs){
        Hit currenthit;
        if(obj->intersect(r,currenthit,tmin)){
            success=true;
            if(currenthit.getT()<h.getT())
            h=currenthit;
        }
    }
    return success;


}
