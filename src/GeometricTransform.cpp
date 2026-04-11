#include "GeometricTransform.hpp"

DBRT::GeometricTransform::GeometricTransform()
{
}

DBRT::GeometricTransform::GeometricTransform(const Mat44f &localToWorld, const Mat44f &worldToLocal)
{
    this->localToWorldTransform = localToWorld;
    this->worldToLocalTransform = worldToLocal;

    //std::clog << "GeometricTransform constructor\n";
    //printMat(localToWorldTransform);
    //printMat(worldToLocalTransform);
}

DBRT::GeometricTransform::~GeometricTransform()
{
}

void DBRT::GeometricTransform::setTransform(const Vec3f &translation, const Vec3f &rotation, const Vec3f &scale)
{
    Mat44f translationMat, rotationMatX, rotationMatY, rotationMatZ, scaleMat;
    float cosRotX = cosf(rotation[0]);
    float sinRotX = sinf(rotation[0]);
    float cosRotY = cosf(rotation[1]);
    float sinRotY = sinf(rotation[1]);
    float cosRotZ = cosf(rotation[2]);
    float sinRotZ = sinf(rotation[2]);

    // Setar valores da matrix de translacao
    /* translationMat[3][0] = translation[0];
    translationMat[3][1] = translation[1];
    translationMat[3][2] = translation[2]; */
    translationMat[0][3] = translation[0];
    translationMat[1][3] = translation[1];
    translationMat[2][3] = translation[2];

    // Setar valores das matrizes de rotacao
    rotationMatX[1][1] = cosRotX;
    rotationMatX[1][2] = -sinRotX;
    rotationMatX[2][1] = sinRotX;
    rotationMatX[2][2] = cosRotX;

    rotationMatY[0][0] = cosRotY;
    rotationMatY[0][2] = sinRotY;
    rotationMatY[2][0] = -sinRotY;
    rotationMatY[2][2] = cosRotY;

    rotationMatZ[0][0] = cosRotZ;
    rotationMatZ[0][1] = -sinRotZ;
    rotationMatZ[1][0] = sinRotZ;
    rotationMatZ[1][1] = cosRotZ;

    // Setar valores da matriz de escala
    scaleMat[0][0] = scale[0];
    scaleMat[1][1] = scale[1];
    scaleMat[2][2] = scale[2];

    // Combinar as matrizes para obter a matrix de transformacao completa
    //this->localToWorldTransform = translationMat*(scaleMat*(rotationMatX*(rotationMatY*rotationMatZ)));
    this->localToWorldTransform = translationMat*(scaleMat*(rotationMatX*(rotationMatY*rotationMatZ)));
    //this->localToWorldTransform = translationMat*(scaleMat*(rotationMatZ*(rotationMatY*rotationMatX)));
    this->worldToLocalTransform = this->localToWorldTransform.inverse();

    //std::clog << "--- Set transform ---\n";
    //printMat(localToWorldTransform);
    //std::clog << "-\n";
    //printMat(worldToLocalTransform);
    //std::clog << "---------------------\n";
}

Mat44f DBRT::GeometricTransform::getLocalToWorldMatrix() const
{
    return this->localToWorldTransform;
}

Mat44f DBRT::GeometricTransform::getWorldToLocalMatrix() const
{
    return this->worldToLocalTransform;
}

DBRT::Ray DBRT::GeometricTransform::applyTransform(const Ray &inputRay, bool directionFlag)
{
    Ray outputRay;
    if(directionFlag == DBRT::LOCAL_TO_WORLD)
    {
        // Transformacao localToWorld
        outputRay.orig = this->applyTransform(inputRay.orig, DBRT::LOCAL_TO_WORLD);
        outputRay.dest = this->applyTransform(inputRay.dest, DBRT::LOCAL_TO_WORLD);
        outputRay.direction = outputRay.dest - outputRay.orig;
    }
    else
    {
        // Transformacao worldToLocal
        outputRay.orig = this->applyTransform(inputRay.orig, DBRT::WORLD_TO_LOCAL);
        outputRay.dest = this->applyTransform(inputRay.dest, DBRT::WORLD_TO_LOCAL);
        outputRay.direction = outputRay.dest - outputRay.orig;
    }

    return outputRay;
}

Coord3f DBRT::GeometricTransform::applyTransform(const Coord3f &inputVector, bool directionFlag)
{
    Vec4f tempVec(inputVector, 1.0);
    Vec4f resultVec;
    if(directionFlag == DBRT::LOCAL_TO_WORLD)
    {
        resultVec = this->localToWorldTransform*tempVec;
    }
    else
    {
        resultVec = this->worldToLocalTransform*tempVec;
    }

    Coord3f res{resultVec.x, resultVec.y, resultVec.z};
    return res;
}

DBRT::GeometricTransform DBRT::GeometricTransform::operator*(const GeometricTransform &rhs)
{
    // Calcular o produto das duas matrizes localToWorld, e depois calcula a matrix worldToLocal
    Mat44f loc2WorRes = this->localToWorldTransform*rhs.localToWorldTransform;
    Mat44f wor2LocRes = loc2WorRes.inverse();

    // Gerar a transformacao final
    GeometricTransform finalRes(loc2WorRes,wor2LocRes);
    return finalRes;
}

DBRT::GeometricTransform DBRT::GeometricTransform::operator=(const GeometricTransform &rhs)
{
    if(this != &rhs)
    {
        //std::clog << "Passei aqui! operator =\n";
            //this->print(rhs.forwardTransform);
            //this->print(rhs.getForwardMatrix());
        this->localToWorldTransform = rhs.localToWorldTransform;
            //this->forwardTransform = rhs.forwardTransform;
        this->worldToLocalTransform = rhs.worldToLocalTransform;
        //this->backwardTransform = rhs.backwardTransform;
        //this->printMat(localToWorldTransform);
        //std::clog << std::endl;
    }
    return *this;
}

void DBRT::GeometricTransform::printMat(const Mat44f &matrix)
{
    for(unsigned int i=0; i<4; i++)
    {
        for(unsigned int j=0; j<4; j++)
        {
            std::cout << std::fixed << std::setprecision(3) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
