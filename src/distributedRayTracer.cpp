#include <iostream>
#include "CommonDefinitions.hpp"
#include "Vectors.hpp"
#include "Scene.hpp"
#include "BinaryPPM.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

int main()
{
    std::string sceneFileName = "scenes/testScene3.scndescr";
    DBRT::Renderer renderer(sceneFileName);
    //DBRT::Scene testScene;
    //DBRT::BinaryPPM imgFile(1280, 720);
    //DBRT::BinaryPPM imgFile(640, 360);  // 16:9
    DBRT::BinaryPPM imgFile(1024, 576, "rayTracingEsfera.ppm");  // 16:9
    //std::clog << "Antes de renderizar a imagem\n";
    renderer.render(imgFile);
    //testScene.render(imgFile);
    //std::clog << "Apos renderizar a imagem\n";
    //imgFile.writeImageFile("rayTracingEsfera.ppm");
    //std::clog << "Imagem escrita no arquivo com sucesso\n";

    return 0;
}
