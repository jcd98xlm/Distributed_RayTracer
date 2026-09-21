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
    // Programa de testes
    std::string sceneFileName1 = "scenes/testScene1.scndescr";
    std::string sceneFileName2 = "scenes/testScene2.scndescr";
    std::string sceneFileName3 = "scenes/testScene3.scndescr";

    // Tamanhos 16:9  1280*720  1024*576  640*360
    DBRT::Renderer renderer(sceneFileName1);
    DBRT::BinaryPPM imgFile1(1280, 720, "rayTracingEsfera1.ppm");  // 16:9
    renderer.render(imgFile1);

    DBRT::Renderer renderer2(sceneFileName2);
    DBRT::BinaryPPM imgFile2(640, 360, "rayTracingEsfera2.ppm");  // 16:9
    renderer2.render(imgFile2);

    DBRT::Renderer renderer3(sceneFileName3);
    DBRT::BinaryPPM imgFile3(1024, 576, "rayTracingEsfera3.ppm");  // 16:9
    renderer3.render(imgFile3);

    return 0;
}
