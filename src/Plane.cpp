#include "Plane.hpp"
#include "MathComparisons.hpp"
#include <cmath>

DBRT::Plane::Plane()
{
}

DBRT::Plane::~Plane()
{
}

bool DBRT::Plane::testIntersection(const Ray &castRay, Coord3f &intersectionPoint, Vec3f &localNormal, Color3f &localColor)
{
    // Aplicar transformacao worldToLocal em uma copia do raio
    Ray bckRay = this->transformMatrix.applyTransform(castRay,DBRT::WORLD_TO_LOCAL);
    Vec3f vhat = bckRay.direction;
    vhat.normalize();

    // Testar se tem interseccao, ou seja se o raio nao eh paralelo ao plano
    // TODO melhorar a comparacao
    if(!almostEqual(vhat.z, 0.0f, std::numeric_limits<float>::epsilon()))
    {
        // Existe uma interseccao
        double t = bckRay.orig.y / -vhat.y;

        // Se t for negativo, entao a interseccao esta atras da camera, e deve ser ignorada
        if(t > 0.0)
        {
            // Calcular valores de u e v
            double u = bckRay.orig.x + vhat.x*t;
            double v = bckRay.orig.z + vhat.z*t;

            // Se a magnitude de u e v forem menores ou iguais a 1, entao devemos estar inseridos no plano
            if(fabs(u) <= 1.0 && fabs(v) <= 1.0)
            {
                // Calcula o ponto de interseccao
                Coord3f poi = bckRay.orig + t*vhat;

                // Converte novamente para as coordenadas globais
                intersectionPoint = this->transformMatrix.applyTransform(poi, DBRT::LOCAL_TO_WORLD);

                // Calcular a normal local
                Vec3f localOrigin {0.0};
                Vec3f normalvector {0.0, 1.0, 0.0};
                Vec3f globalOrigin = this->transformMatrix.applyTransform(localOrigin, DBRT::LOCAL_TO_WORLD);
                localNormal = this->transformMatrix.applyTransform(normalvector, DBRT::LOCAL_TO_WORLD) - globalOrigin;
                localNormal.normalize();

                // Devolve a cor base
                localColor = this->baseColor;

                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    return false;
}