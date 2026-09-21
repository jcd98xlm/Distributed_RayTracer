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
    // Construir vetor do ponto de interseccao ate a fonte de luz
    Vec3f lightDirection = (this->lightPosition - intersectionPoint).normalize();
    Coord3f startPoint = intersectionPoint;

    // Construir um raio de sombreamento, ou shadow ray
    Ray shadowRay(intersectionPoint, this->lightPosition);
    Coord3f shadowIntersectionPoint;
    Vec3f shadowLocalNormal;
    Color3f shadowColor;

    // Testar se a luz e visivel do ponto de interseccao
    for(auto otherObjects : objectList)
    {
        // Ignora objeto atual para evitar auto interseccao
        if(otherObjects != currentObject)
        {
            bool hit = otherObjects->testIntersection(shadowRay, shadowIntersectionPoint, shadowLocalNormal, shadowColor);
            if(hit)
            {
                // Se atingiu outro objeto, entao esta na sombra (assumindo que existam apenas objetos opacos por enquanto)
                color = this->lightColor;
                intensity = 0.0;
                return false;
            }
        }
        //else
            //std::cerr << "Testei comigo mesmo\n";
    }

    // Se a luz nao esta bloqueada, calculamos sua contribuicao
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
