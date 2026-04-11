#include "GeometricObject.hpp"

DBRT::GeometricObject::GeometricObject()
{
}

DBRT::GeometricObject::~GeometricObject()
{
}

void DBRT::GeometricObject::setTransformMatrix(const GeometricTransform &newTransformMatrix)
{
    this->transformMatrix = newTransformMatrix;
    //std::clog << "------------------------------------------------\n";
    //std::clog << "Passei por setTransformMatrix\n";
    //DBRT::GeometricTransform::print(transformMatrix.getForwardMatrix());
    //DBRT::GeometricTransform::printMat(this->transformMatrix.localToWorldTransform);
    //    std::clog << std::endl;
    //    std::clog << "----backward Matrix\n";
    //DBRT::GeometricTransform::printMat(this->transformMatrix.worldToLocalTransform);
    //    std::clog << std::endl;
    //std::clog << "------------------------------------------------\n";
}
