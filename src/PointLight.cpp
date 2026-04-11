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

    // Cacular o angulo entre a normal local e o raio de luz, assumindo que a normal eh um vetor unitario
    // a.b = |a|*|b|*cos(Theta), como ambos a e b sao unitarios logo a.b = 1*1*cos(Theta)
    float angle = acosf(localNormal.dotProduct(lightDirection));

    // Se a normal nao esta apontada para a luz, entao nao temos iluminacao nesse ponto
    // valor ref 1.5708 ou 1.2(meu) 5,89 1.89
    double angleRef = 1.5708;
    if(angle > angleRef)
    {
        color = this->lightColor;
        intensity = 0.0;//0.0
        return false;
    }
    else
    {
        color = this->lightColor;
        //intensity = 1.0;
        intensity = this->lightIntensity*(1.0 - (angle/angleRef));
        return true;
    }
    /*
    double angleRef = 1.89;
    if(angle > angleRef)
    {
        color = this->lightColor;
        intensity = 0.0;
        return false;
    }
    else
    {
        color = this->lightColor;
        intensity = this->lightIntensity*(1.0 - (angle/angleRef));
        return true;
    }
    */
}
