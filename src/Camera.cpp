#include "Camera.hpp"

DBRT::Camera::Camera()
{
    this->cameraPosition = Coord3f {0.0, -10.0, 0.0};
    this->cameraLookAt = Coord3f {0.0, 0.0, 0.0};
    this->cameraUpDirection = Vec3f {0.0, 1.0, 0.0}; // 0 1 0
    this->cameraFocusDistance = 9.5;//2.5
    this->cameraFocalLength = 1.0;
    this->cameraLensRadius = 0.05;
    this->cameraHorizontalSize = 1.0;
    this->cameraAspectRatio = 1.0;
}

void DBRT::Camera::setPosition(const Coord3f &newPosition)
{
    this->cameraPosition = newPosition;
}

void DBRT::Camera::setLookAt(const Coord3f &newLookAt)
{
    this->cameraLookAt = newLookAt;
}

void DBRT::Camera::setUpDirection(const Vec3f &upDirection)
{
    this->cameraUpDirection = upDirection;
}

void DBRT::Camera::setFocusDistance(float newFocusDistance)
{
    this->cameraFocusDistance = newFocusDistance;
}

void DBRT::Camera::setFocalLength(float newLength)
{
    this->cameraFocalLength = newLength;
}

void DBRT::Camera::setLensRadius(float newLensRadius)
{
    this->cameraLensRadius = newLensRadius;
}

void DBRT::Camera::setHorizontalSize(float newHorizontalSize)
{
    this->cameraHorizontalSize = newHorizontalSize;
}

void DBRT::Camera::setAspectRatio(float newAspectRatio)
{
    this->cameraAspectRatio = newAspectRatio;
}

Coord3f DBRT::Camera::getPosition() const
{
    return this->cameraPosition;
}

Coord3f DBRT::Camera::getLookAt() const
{
    return this->cameraLookAt;
}

Vec3f DBRT::Camera::getUpDirection() const
{
    return this->cameraUpDirection;
}

Vec3f DBRT::Camera::getUVec() const
{
    return this->projectionScreenU;
}

Vec3f DBRT::Camera::getVVec() const
{
    return this->projectionScreenV;
}

Coord3f DBRT::Camera::getScreenCenter() const
{
    return this->projectionScreenCenter;
}

float DBRT::Camera::getFocusDistance() const
{
    return this->cameraFocusDistance;
}

float DBRT::Camera::getFocalLength() const
{
    return this->cameraFocalLength;
}

float DBRT::Camera::getLensRadius() const
{
    return this->cameraLensRadius;
}

float DBRT::Camera::getHorizontalSize() const
{
    return this->cameraHorizontalSize;
}

float DBRT::Camera::getAspectRatio() const
{
    return this->cameraAspectRatio;
}

bool DBRT::Camera::generateRay(float projScreenX, float projScreenY, Ray &cameraRay)
{
    // Assumindo projScreenX e projScreenY estão normalizados entre -1 e 1
    // Calcular a localizacao do ponto na tela em relacao as coordenadas globais
    Vec3f screenWorldPart1 = this->projectionScreenCenter + (this->projectionScreenU * projScreenX);
    Vec3f screenWorldCoordinate = screenWorldPart1 + (this->projectionScreenV * projScreenY);
    // Calcular o raio usando esse ponto e a posicao da camera
    cameraRay.orig = this->cameraPosition;
    cameraRay.dest = screenWorldCoordinate;
    cameraRay.direction = (screenWorldCoordinate - this->cameraPosition).normalize();

    return true;
}

bool DBRT::Camera::generateRay(float projScreenX, float projScreenY, Ray &cameraRay, IRNG &sampler)
{
    // Calcular a localizacao do ponto na tela em relacao as coordenadas globais
    Vec3f screenWorldPart1 = this->projectionScreenCenter + (this->projectionScreenU * projScreenX);
    Vec3f screenWorldCoordinate = screenWorldPart1 + (this->projectionScreenV * projScreenY);

    // Calcular o ponto no plano focal para este pixel
    Vec3f primaryRayDir = (screenWorldCoordinate - this->cameraPosition).normalize();
    // Usa o cosseno do ângulo para projetar no plano focal paralelo à lente
    float cosTheta = primaryRayDir.dotProduct(this->alignmentVector);
    Coord3f focusPoint = this->cameraPosition + primaryRayDir*(this->cameraFocusDistance/cosTheta);

    // TEMPORARIO, alterar na funcao updateCameraGeometry
    Vec3f uNorm = this->projectionScreenU;
    uNorm.normalize();
    Vec3f vNorm = this->projectionScreenV;
    vNorm.normalize();

    // Gerar o ponto amostral na lente
    Coord3f sampPoint = sampler.random_in_unit_disk(sampler) * this->cameraLensRadius;
    Coord3f sampPointOffset = (uNorm*sampPoint.x) + (vNorm*sampPoint.y);
    
    // Calcular o raio usando o ponto amostral e o ponto focal
    cameraRay.orig = this->cameraPosition + sampPointOffset;    
    cameraRay.dest = focusPoint;
    cameraRay.direction = (focusPoint - cameraRay.orig).normalize();    

    return true;
}

void DBRT::Camera::updateCameraGeometry()
{
    // Calcular vetor da posicao da camera ate a posicao que estamos observada
    this->alignmentVector = this->cameraLookAt - this->cameraPosition;
    this->alignmentVector.normalize();
    // Calcular os vetores U e V
    this->projectionScreenU = this->alignmentVector.crossProduct(this->cameraUpDirection);
    this->projectionScreenU.normalize();
    this->projectionScreenV = this->projectionScreenU.crossProduct(this->alignmentVector);
    this->projectionScreenV.normalize();
    // Calcular a posicao do ponto central da tela
    this->projectionScreenCenter = this->cameraPosition + (this->cameraFocalLength * this->alignmentVector);
    // Modificar os vetores U e V para se adequar a proporcao de tela
    this->projectionScreenU = this->projectionScreenU * this->cameraHorizontalSize;
    this->projectionScreenV = this->projectionScreenV * (this->cameraHorizontalSize / this->cameraAspectRatio);
}
