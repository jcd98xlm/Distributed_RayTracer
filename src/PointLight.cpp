#include "PointLight.hpp"

//orig(Coord3f(0.0, 0.0, 0.0)), dest(Coord3f(0.0, 0.0, 0.0)), direction(Vec3f(dest-orig))
DBRT::PointLight::PointLight()
{
    lightPosition = Coord3f{0.0};
    lightColor = Color3f{1.0, 1.0, 1.0};
    lightIntensity = 1.0;
}

DBRT::PointLight::~PointLight()
{
}

bool DBRT::PointLight::computeIllumination(const Coord3f &intersectionPoint, const Coord3f &localNormal, const std::vector<std::shared_ptr<DBRT::GeometricObject>> &objectList, const std::shared_ptr<DBRT::GeometricObject> &currentObject, Color3f &color, float &intensity)
{
    // Contruir vetor do ponto de interseccao ate a fonte de luz
    Vec3f lightDirection = (this->lightPosition - intersectionPoint).normalize();
    Coord3f startPoint = intersectionPoint;

    float cosTheta = localNormal.dotProduct(lightDirection);

    // Se usarmos Lambertian shading temos L = kd*I*cos(theta) = kd*I*max(0,n*l)
    // onde L eh a cor do pixel, kd eh o coeficiente difuso, I eh a intensidade da luz, n eh a normal, l eh a direcao da luz
    float attenuation = (cosTheta > 0.0) ? cosTheta : 0.0;

    if(attenuation > 0.0) 
    {
        // Tem iluminacao nesse ponto
        color = this->lightColor;
        intensity = this->lightIntensity*attenuation;
        return true;
    }
    else
    {
        color = this->lightColor;
        intensity = 0.0;
        return false;
    }
    return false;
}
