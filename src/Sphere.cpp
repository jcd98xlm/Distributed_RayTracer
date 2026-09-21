#include "Sphere.hpp"

DBRT::Sphere::Sphere()
{
}

DBRT::Sphere::~Sphere()
{
}

bool DBRT::Sphere::testIntersection(const Ray &castRay, Coord3f &intersectionPoint, Vec3f &localNormal, Color3f &localColor)
{
    // Aplicar transformacao worldToLocal em uma copia do raio
    Ray bckRay = this->transformMatrix.applyTransform(castRay, DBRT::WORLD_TO_LOCAL);
    Vec3f vhat = bckRay.direction;
    vhat.normalize();

    // Calcular os valores de a,b,c na equacao do segundo grau
    float a = 1.0;
    float b = 2.0*bckRay.orig.dotProduct(vhat);
    float c = bckRay.orig.dotProduct(bckRay.orig) - 1.0;

    // Testar se tem interseccao
    Coord3f localIntersectionPoint;
    float discriminant = b*b - 4.0*a*c;
    if(discriminant > 0.0)
    {
        float numSqrt = sqrtf(discriminant);
        float t1 = (-b + numSqrt)/(2.0*a);
        float t2 = (-b - numSqrt)/(2.0*a);

        // Se t1 ou t2 for negativo, entao pelo menos uma parte do objeto esta atras da camera, e deve ser ignorado
        if(t1 < 0.0 || t2 < 0.0)
            return false;
        else
        {
            // Determinar qual ponto esta mais proximo
            if(t1 < t2)
            {
                localIntersectionPoint = bckRay.orig + (vhat*t1);
            }
            else
            {
                localIntersectionPoint = bckRay.orig + (vhat*t2);
            }

            // Transformar o ponto de volta para as coordenadas globais
            intersectionPoint = this->transformMatrix.applyTransform(localIntersectionPoint, DBRT::LOCAL_TO_WORLD);

            // Calcular a normal local, para uma esfera centrada na origem do sistema local
            Coord3f objOrigin{0.0};
            Coord3f newObjOrigin = this->transformMatrix.applyTransform(objOrigin, DBRT::LOCAL_TO_WORLD);
            localNormal = intersectionPoint - newObjOrigin;
            localNormal.normalize();

            localColor = this->baseColor;
        }
        return true;        
    }
    else
        return false;
}
