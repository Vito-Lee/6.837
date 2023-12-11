#include"raytracer.h"
#include<cmath>
void raytracer::ReadFromFile(char* input_file)
{
    //格式为
    /*
    OrthographicCamera{
        ````
    }
    Material{
        ```
    }
    Group{
        ....
    }
    */
   _sceneparser=std::make_shared<SceneParser>(input_file);

}
void raytracer::renderToImage(Image& image){
    Vec3f bgcolor=_sceneparser->getBackgroundColor();
    image.SetAllPixels(bgcolor);
    auto *camera=dynamic_cast<OrthographicCamera*>(_sceneparser->getCamera());
    assert(camera!=nullptr);
    auto *Group=_sceneparser->getGroup();
    //遍历屏幕 发射光线
    for(int i=0;i<image.Width();i++)
    {
        for(int j=0;j<image.Height();j++)
        {
            //发射原点的范围为（0,0）->(1,1)
            Vec2f p((float)i/image.Width(),(float)j/image.Height());
            auto ray=camera->generateRay(p);
            Hit h;
            if(Group->intersect(ray,h,camera->getTMin())){
                //有碰撞则将颜色转为最近碰撞点的颜色
                auto* material=h.getMaterial();
                image.SetPixel(i,j,material->getDiffuseColor());
            }



        }
    }


}

void raytracer::renderDepthToImage(Image &image,float depMin,float depMax)
{
    Vec3f blackcolor(0.f,0.f,0.f),whitecolor(1.f,1.f,1.f);
    image.SetAllPixels(blackcolor);
    auto *camera=dynamic_cast<OrthographicCamera*>(_sceneparser->getCamera());
    assert(camera!=nullptr);
    auto *Group=_sceneparser->getGroup();
    //遍历屏幕 发射光线
    for(int i=0;i<image.Width();i++)
    {
        for(int j=0;j<image.Height();j++)
        {
            //发射原点的范围为（0,0）->(1,1)
            Vec2f p((float)i/image.Width(),(float)j/image.Height());
            auto ray=camera->generateRay(p);
            Hit hit;
            if(Group->intersect(ray,hit,camera->getTMin())){
                //有碰撞则将颜色转为最近碰撞点的颜色
                auto t=hit.getT();
                //跟传进来的深度范围比较，若超过最大值则钳制为最大值，最小值同理
                t=std::min(depMax,t);
                t=std::max(depMin,t);
                auto weight=(float)(t-depMin)/(depMax-depMin);
                Vec3f color;
                //越远越黑，越近越白
                Vec3f::WeightedSum(color,blackcolor,weight,whitecolor,1-weight);
                image.SetPixel(i,j,color);

            }



        }
    }
}
