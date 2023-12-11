#include"OrthographicCamera.h"
#include<random>
#include<limits>
Ray OrthographicCamera::generateRay(Vec2f point)
{
    //光线原点取值
    auto orign=center+(point.x()-0.5)*_size*_horizontal+(point.y()-0.5)*_size*_up;
    return Ray(orign,_direction);


}


OrthographicCamera::OrthographicCamera(const Vec3f& point,const Vec3f& direction,const Vec3f& up,float size){
    center=point;
    _size=size;
    //构建相机坐标系，direction为x轴，up和direction叉乘出z轴，z和x叉乘出y轴
    //direction要归一化

    _direction=direction;
    _direction.Normalize();
    Vec3f::Cross3(_horizontal,up,_direction);
    _horizontal.Normalize();
    Vec3f::Cross3(_up,_horizontal,_direction);
    _up.Normalize();


}
float OrthographicCamera::getTMin()const{
    return std::numeric_limits<float>::lowest();
}

