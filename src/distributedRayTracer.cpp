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
    std::string sceneFileName4 = "scenes/testScene4.scndescr";
    std::string sceneFileName5 = "scenes/testCornellBox.scndescr";

    // Tamanhos 16:9  1280*720  1024*576  640*360
    DBRT::Renderer renderer = DBRT::Renderer();
    renderer.loadScene(sceneFileName1);
    renderer.render();

    DBRT::Renderer renderer2 = DBRT::Renderer();
    renderer2.loadScene(sceneFileName2);
    renderer2.render();

    DBRT::Renderer renderer3 = DBRT::Renderer();
    renderer3.loadScene(sceneFileName3);
    renderer3.render();

    DBRT::Renderer renderer4 = DBRT::Renderer();
    renderer4.loadScene(sceneFileName4);
    renderer4.render();

    DBRT::Renderer renderer5 = DBRT::Renderer();
    renderer5.loadScene(sceneFileName5);
    renderer5.render();
    
    return 0;
}
