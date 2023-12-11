
#include "raytracer.h"

#include <cmath>
#include <vector>

#include "light.h"

void RayTracer::readSceneFromFile(char *input_file) {
    _sceneParser = std::make_shared<SceneParser>(input_file);
}

void RayTracer::renderToImage(Image &img, bool shade_back) {
    auto blackColor = Vec3f(0.f, 0.f, 0.f);
    auto bgColor = _sceneParser->getBackgroundColor();
    img.SetAllPixels(bgColor);

    auto *camera = _sceneParser->getCamera();
    assert(camera != nullptr);

    auto group = _sceneParser->getGroup();

    auto nLights = _sceneParser->getNumLights();
    std::vector<Light*> lights(static_cast<unsigned long>(nLights));
    for (int i = 0; i < nLights; ++i) {
        lights[i] = _sceneParser->getLight(i);
    }
    auto ambient = _sceneParser->getAmbientLight();

    for (int y = 0; y < img.Width(); ++y) {
        for (int x = 0; x < img.Height(); ++x) {
            Vec2f p(float(x) / img.Width(), float(y) / img.Height());
            auto ray = camera->generateRay(p);
            Hit hit;
            if (group->intersect(ray, hit, camera->getTMin())) {
                auto norm = hit.getNormal();
                bool isBackSide = norm.Dot3(ray.getDirection()) > 0;
                if (isBackSide) {
                    if (shade_back)
                        //法向量取反，来处理背面
                        norm.Negate();
                    else {
                        img.SetPixel(x, y, blackColor);
                        continue;
                    }
                }

                auto m = hit.getMaterial();
                auto cObj = m->getDiffuseColor();
                //光照公式：color=Cobject*Cambient+Sum(Li*N*cLight*Cobject)
                auto color = ambient * cObj;
                for (int i = 0; i < nLights; ++i) {
                    Vec3f intersection = hit.getIntersectionPoint(), lightDir, cLight;
                    lights[i]->getIllumination(intersection, lightDir, cLight);
                    color += std::max(0.f, lightDir.Dot3(norm)) * cLight * cObj;
                }
                img.SetPixel(x, y, color);
            }
        }
    }
}

void RayTracer::renderDepthToImage(Image &img, float depMin, float depMax) {
    auto blackColor = Vec3f(0.f, 0.f, 0.f), whiteColor = Vec3f(1.f, 1.f, 1.f);
    img.SetAllPixels(blackColor);

    auto *camera = _sceneParser->getCamera();
    assert(camera != nullptr);

    auto group = _sceneParser->getGroup();

    for (int y = 0; y < img.Width(); ++y) {
        for (int x = 0; x < img.Height(); ++x) {
            Vec2f p(float(x) / img.Width(), float(y) / img.Height());
            auto ray = camera->generateRay(p);
            Hit hit;
            if (group->intersect(ray, hit, camera->getTMin())) {
                auto t = hit.getT();
                t = std::min(depMax, t);
                t = std::max(depMin, t);
                float weight = (t - depMin) / (depMax - depMin);
                Vec3f color;
                Vec3f::WeightedSum(color, blackColor, weight, whiteColor, 1 - weight);
                img.SetPixel(x, y, color);
            }
        }
    }
}

void RayTracer::renderNormalToImage(Image &img) {
    auto blackColor = Vec3f(0.f, 0.f, 0.f);
    img.SetAllPixels(blackColor);

    auto *camera = _sceneParser->getCamera();
    assert(camera != nullptr);

    auto group = _sceneParser->getGroup();

    for (int y = 0; y < img.Width(); ++y) {
        for (int x = 0; x < img.Height(); ++x) {
            Vec2f p(float(x) / img.Width(), float(y) / img.Height());
            auto ray = camera->generateRay(p);
            Hit hit;
            if (group->intersect(ray, hit, camera->getTMin())) {
                auto norm = hit.getNormal();
                Vec3f color = Vec3f(std::fabs(norm.x()), std::fabs(norm.y()), std::fabs(norm.z()));
                img.SetPixel(x, y, color);
            }
        }
    }
}
