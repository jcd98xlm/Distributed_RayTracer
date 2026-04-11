#include "Camera.hpp"

DBRT::Camera::Camera()
{
    this->cameraPosition = Coord3f {0.0, -10.0, 0.0};
    this->cameraLookAt = Coord3f {0.0, 0.0, 0.0};
    this->cameraUpDirection = Vec3f {0.0, 0.0, 1.0}; // 0 1 0
    this->cameraLength = 1.0;
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

void DBRT::Camera::setLength(float newLength)
{
    this->cameraLength = newLength;
}

/* void DBRT::Camera::setHorizontalSize(unsigned int newHorizontalSize)
{
    this->cameraHorizontalSize = newHorizontalSize;
} */
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

float DBRT::Camera::getLength() const
{
    return this->cameraLength;
}

/* unsigned int DBRT::Camera::getHorizontalSize() const
{
    return this->cameraHorizontalSize;
} */
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
    // Calcular a localizacao do ponto na tela em relacao as coordenadas globais
    Vec3f screenWorldPart1 = this->projectionScreenCenter + (this->projectionScreenU * projScreenX);
    Vec3f screenWorldCoordinate = screenWorldPart1 + (this->projectionScreenV * projScreenY);
    // Calcular o raio usando esse ponto e a posicao da camera
    cameraRay.orig = this->cameraPosition;
    cameraRay.dest = screenWorldCoordinate;
    cameraRay.direction = screenWorldCoordinate - this->cameraPosition;

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
    this->projectionScreenCenter = this->cameraPosition + (this->cameraLength * this->alignmentVector);
    //this->projectionScreenCenter = this->cameraPosition + (this->alignmentVector * this->cameraLength);
    // Modificar os vetores U e V para se adequar a proporcao de tela
    this->projectionScreenU = this->projectionScreenU * this->cameraHorizontalSize;
    this->projectionScreenV = this->projectionScreenV * (this->cameraHorizontalSize / this->cameraAspectRatio);
}
