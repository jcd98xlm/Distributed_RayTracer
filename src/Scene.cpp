#include "Scene.hpp"
#include <fstream>
//temporario
#include <chrono>

DBRT::Scene::Scene()
{
    
}

DBRT::Scene::~Scene()
{
}

DBRT::Camera &DBRT::Scene::getCamera()
{
    return this->sceneCamera;
}

std::vector<std::shared_ptr<DBRT::GeometricObject>> &DBRT::Scene::getObjectList()
{
    return this->sceneObjectList;
}

std::vector<std::shared_ptr<DBRT::LightSource>> &DBRT::Scene::getLightList()
{
    return this->sceneLightList;
}

Color3f &DBRT::Scene::getBackgroundColor()
{
    return this->backgroundColor;
}

bool DBRT::Scene::generateScene(const std::string &fileName)
{
    std::string line;
    std::ifstream inputFile(fileName);
    if(!inputFile.is_open())
    {
        std::cerr << "Nao foi possivel abrir o arquivo contendo a cena\n";
        return false;
    }

    std::getline(inputFile,line);
    if(line.compare("#SCENEFILE") == 0)
    {
        //std::cout << "Li a 1a linha: " << line << std::endl;    
        while(std::getline(inputFile, line))
        {
            std::stringstream ss(line);
            ss >> line;
            if(line.compare("nobjs") == 0)
            {
                int nobj;
                ss >> nobj;
                //std::cout << "Quantidade de objetos na cena eh: " << nobj << std::endl;
                // ler os objs
                for(int i=0;i<nobj;i++)
                {
                    std::getline(inputFile, line);
                    //std::cout << "Lendo objeto " << i << " " << line << std::endl;
                    ss.str(line);
                    ss.clear();
                    ss >> line;
                    if(line.compare("obj") == 0)
                    {
                        float a,b,c,d,e,f,g,h,j;
                        float R,G,B;
                        // ler tipo de objeto
                        ss >> line;
                        if(line.compare("type:sphere") == 0)
                        {
                            sceneObjectList.push_back(std::make_shared<DBRT::Sphere>(DBRT::Sphere()));                            
                            ss >> line;
                            if(line.compare("transform:") == 0)
                            {                            
                                // ler o transform
                                ss >> a >> b >> c >> d >> e >> f >> g >> h >> j;
                                //std::cout << "\tTransform lido: " << a << " " << b << " " << c << " " << d << " " << e << " " << f << " " << g << " " << h << " " << j << std::endl;
                                GeometricTransform t;
                                t.setTransform(Vec3f{a, b, c}, Vec3f{d, e, f}, Vec3f{g, h, j});
                                sceneObjectList.at(i)->setTransformMatrix(t);
                                
                                ss >> line;
                                if(line.compare("color:") == 0)
                                {
                                    // ler a cor                                    
                                    ss >> R >> G >> B;
                                    //std::cout << "\tCor lida: " << R << " " << G << " " << B << std::endl;
                                    sceneObjectList.at(i)->baseColor = Color3f{R, G, B};
                                }
                            }                            
                        }
                        else if(line.compare("type:plane") == 0)
                        {
                            sceneObjectList.push_back(std::make_shared<DBRT::Plane>(DBRT::Plane()));
                            ss >> line;
                            if(line.compare("transform:") == 0)
                            {
                                // ler o transform
                                ss >> a >> b >> c >> d >> e >> f >> g >> h >> j;
                                //std::cout << "\tTransform lido: " << a << " " << b << " " << c << " " << d << " " << e << " " << f << " " << g << " " << h << " " << j << std::endl;
                                GeometricTransform t;
                                t.setTransform(Vec3f{a, b, c}, Vec3f{d, e, f}, Vec3f{g, h, j});
                                sceneObjectList.at(i)->setTransformMatrix(t);

                                ss >> line;
                                if(line.compare("color:") == 0)
                                {
                                    // ler a cor
                                    ss >> R >> G >> B;
                                    //std::cout << "\tCor lida: " << R << " " << G << " " << B << std::endl;
                                    sceneObjectList.at(i)->baseColor = Color3f{R, G, B};
                                }
                            }
                        }
                        else
                        {
                            std::cout << "Tipo de objeto desconhecido - " << line << std::endl;
                        }
                    }
                }                
            }
            else if(line.compare("nlights") == 0)
            {
                int nlights;
                ss >> nlights;
                //std::cout << "Quantidade de luzes na cena eh: " << nlights << std::endl;
                // ler os objs
                for(int i=0;i<nlights;i++)
                {
                    std::getline(inputFile, line);
                    //std::cout << "Lendo luz " << i << " " << line << std::endl;
                    ss.str(line);
                    ss.clear();
                    ss >> line;
                    if(line.compare("light") == 0)
                    {
                        float x,y,z;
                        float intensity;
                        float R,G,B;
                        // ler tipo de luz
                        ss >> line;
                        if(line.compare("type:point") == 0)
                        {
                            sceneLightList.push_back(std::make_shared<DBRT::PointLight>(DBRT::PointLight()));
                            ss >> line;
                            if(line.compare("position:") == 0)
                            {
                                // ler posicao
                                ss >> x >> y >> z;
                                //std::cout << "\tPosicao lida: " << x << " " << y << " " << z << std::endl;
                                sceneLightList.at(i)->lightPosition = Coord3f{x, y, z};

                                ss >> line;
                                if(line.compare("intensity:") == 0)
                                {
                                    // ler intensidade
                                    ss >> intensity;
                                    //std::cout << "\tIntensidade lida: " << intensity << std::endl;
                                    sceneLightList.at(i)->lightIntensity = intensity;

                                    ss >> line;
                                    if(line.compare("color:") == 0)
                                    {
                                        // ler a cor
                                        ss >> R >> G >> B;
                                        //std::cout << "\tCor lida: " << R << " " << G << " " << B << std::endl;
                                        sceneLightList.at(i)->lightColor = Color3f{R, G, B};
                                    }
                                }
                            }
                        }
                        else
                        {
                            std::cout << "Tipo de luz desconhecida - " << line << std::endl;
                        }
                    }
                }
            }
            else if(line.compare("camera") == 0)
            {
                //std::cout << "Lendo camera: " << line << std::endl;
                float x,y,z;
                float lx,ly,lz;
                float udx,udy,udz;
                float horSize;
                float ratioup,ratiodown;
                ss >> line;
                if(line.compare("position:") == 0)
                {
                    ss >> x >> y >> z;
                    //std::cout << "\tPosicao lida: " << x << " " << y << " " << z << std::endl;
                    sceneCamera.setPosition(Coord3f{x, y, z});

                    ss >> line;
                    if(line.compare("lookat:") == 0)
                    {
                        ss >> lx >> ly >> lz;
                        //std::cout << "\tLookAt lido: " << lx << " " << ly << " " << lz << std::endl;
                        sceneCamera.setLookAt(Coord3f{lx, ly, lz});

                        ss >> line;
                        if(line.compare("updir:") == 0)
                        {
                            ss >> udx >> udy >> udz;
                            //std::cout << "\tupDir lida: " << udx << " " << udy << " " << udz << std::endl;
                            sceneCamera.setUpDirection(Vec3f{udx, udy, udz});

                            ss >> line;
                            if(line.compare("horizsize:") == 0)
                            {
                                ss >> horSize;
                                //std::cout << "\tHorizontalSize lido: " << horSize << std::endl;
                                sceneCamera.setHorizontalSize(horSize);
                                    
                                ss >> line;
                                if(line.compare("aspectratio:") == 0)
                                {
                                    ss >> ratioup >> ratiodown;
                                    //std::cout << "\tAspectRatio lido: " << ratioup << " " << ratiodown << "  ratio efetivo:" << ratioup/ratiodown << std::endl;
                                    sceneCamera.setAspectRatio(ratioup/ratiodown);
                                }
                            }
                        }
                    }
                }
                sceneCamera.updateCameraGeometry();
            }
            else if(line.compare("background") == 0)
            {
                //std::cout << "Lendo cor do background: " << line << std::endl;
                ss >> line;
                if(line.compare("color:") == 0)
                {
                    float R,G,B;
                    ss >> R >> G >> B;
                    //std::cout << "\tCor lida: " << R << " " << G << " " << B << std::endl;
                    backgroundColor = Color3f{R, G, B};
                }
            }
            else
                std::cerr << "Linha do arquivo esta incorreta: " << line << std::endl;            
        }
    }
    else
    {    
        std::cout << "Arquivo invalido" << std::endl;
        return false;
    }
    
    inputFile.close();
    return true;
}

/*
    // antigo generateScene()
    std::clog << "------------------------------------------------\n";
    std::clog << "---------------------Scene----------------------\n";
    
    auto stamp = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration;

    // Ajustar camera
    std::clog << "--- Ajustar a camera ---\n";
    sceneCamera.setPosition(Coord3f{0.0, 1.0, 10.0});
    sceneCamera.setLookAt(Coord3f{0.0});
    sceneCamera.setUpDirection(Vec3f{0.0, 1.0, 0.0});
    sceneCamera.setHorizontalSize(0.250); //0.25 ou 1.0
    sceneCamera.setAspectRatio(16.0/9.0);
    sceneCamera.updateCameraGeometry();

    duration = std::chrono::high_resolution_clock::now() - stamp;
    std::cout << "\tTempo gasto para ajustar a camera: " << duration.count() << " s\n";
    stamp = std::chrono::high_resolution_clock::now();

    // Adicionar objetos
    std::clog << "--- Adicionar objetos ---\n";
    sceneObjectList.push_back(std::make_shared<DBRT::Sphere>(DBRT::Sphere()));
    sceneObjectList.push_back(std::make_shared<DBRT::Sphere>(DBRT::Sphere()));
    sceneObjectList.push_back(std::make_shared<DBRT::Sphere>(DBRT::Sphere()));

    sceneObjectList.push_back((std::make_shared<DBRT::Plane>(DBRT::Plane())));

    //sceneObjectList.at(0)->baseColor = Color3f{64.0, 128.0, 200.0};
    //sceneObjectList.at(0)->baseColor = Color3f{64.0, 128.0, 200.0};
    //sceneObjectList.at(1)->baseColor = Color3f{255.0, 128.0, 0.0};
    //sceneObjectList.at(2)->baseColor = Color3f{128.0, 0.0, 128.0};

    //sceneObjectList.at(3)->baseColor = Color3f{128.0, 128.0, 128.0};
    sceneObjectList.at(0)->baseColor = Color3f{64.0/255.0, 128.0/255.0, 200.0/255.0};
    sceneObjectList.at(1)->baseColor = Color3f{255.0/255.0, 128.0/255.0, 0.0/255.0};
    sceneObjectList.at(2)->baseColor = Color3f{128.0/255.0, 0.0/255.0, 128.0/255.0};

    sceneObjectList.at(3)->baseColor = Color3f{128.0/255.0, 128.0/255.0, 128.0/255.0};

    GeometricTransform testMat1, testMat2, testMat3, planeMat;
    //testMat1.setTransform(Vec3f{-5.0, -0.5, 0.0},Vec3f{60.0},Vec3f{2.0, 0.75, 1.23});
    testMat1.setTransform(Vec3f{-1.5, 0.0, 0.0},Vec3f{0.0},Vec3f{0.5, 0.75, 0.5});
    
    //testMat2.setTransform(Vec3f{0.0, 0.0, 0.0},Vec3f{0.0},Vec3f{0.75, 2.5, 0.5});
    testMat2.setTransform(Vec3f{0.0, 0.0, 0.0},Vec3f{0.0},Vec3f{0.75, 0.5, 0.5});

    //testMat3.setTransform(Vec3f{5.5, 1.0, 0.0},Vec3f{0.0},Vec3f{0.75, 0.75, 0.75});
    testMat3.setTransform(Vec3f{1.5, 0.0, 0.0},Vec3f{0.0},Vec3f{0.75, 0.75, 0.75});
    
    planeMat.setTransform(Vec3f{0.0, -0.75, 0.0},Vec3f{0.0, 0.0, 0.0},Vec3f{4.0, 1.0, 4.0});

    sceneObjectList.at(0)->setTransformMatrix(testMat1);
    sceneObjectList.at(1)->setTransformMatrix(testMat2);
    sceneObjectList.at(2)->setTransformMatrix(testMat3);
    sceneObjectList.at(3)->setTransformMatrix(planeMat);
    
    duration = std::chrono::high_resolution_clock::now() - stamp;
    std::cout << "\tTempo gasto para construir os objetos: " << duration.count() << " s\n";

    stamp = std::chrono::high_resolution_clock::now();

    // Adicionar iluminacao
    std::clog << "--- Adicionar iluminacao ---\n";
    sceneLightList.push_back(std::make_shared<DBRT::PointLight>(DBRT::PointLight()));
    sceneLightList.at(0)->lightPosition = Coord3f{5.0, 10.0, 5.0};
    //sceneLightList.at(0)->lightColor = Color3f{255.0, 255.0, 255.0};
    sceneLightList.at(0)->lightColor = Color3f{255.0/255.0, 255.0/255.0, 255.0/255.0};
    //sceneLightList.at(0)->lightColor = Color3f{5.0, 0.0, 0.0};
    sceneLightList.at(0)->lightIntensity = 0.5;

    duration = std::chrono::high_resolution_clock::now() - stamp;
    std::cout << "\tTempo gasto para ajustar a iluminacao: " << duration.count() << " s\n";

    std::clog << "------------------------------------------------\n";
    return true;
*/

/* bool DBRT::Scene::render(ImageFile &outputImage)
{
    auto stamp = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration;

    unsigned int xSize = outputImage.getWidth();
    unsigned int ySize = outputImage.getHeight();

    // Buffer local para a imagem
    std::vector<Color3f> imgBuffer(xSize*ySize, sizeof(Color3f));

    // Processa os pixels da imagem
    Ray cameraRay;
    Coord3f intPoint;
    Vec3f localNormal;
    Color3f localColor;

    // Pre-calcular fatores de escala para as coordenadas
    //float xScaleFactor = 1.0/(static_cast<float>(xSize)/2.0);
    //float yScaleFactor = 1.0/(static_cast<float>(ySize)/2.0);
    float xScaleFactor = 2.0/static_cast<float>(xSize);
    float yScaleFactor = 2.0/static_cast<float>(ySize);
    //float minDist = 1e6;
    //float maxDist = 0.0;
    for(unsigned int y=0; y<ySize; y++)
    //for(unsigned int x=0; x<xSize; x++)
    {
        for(unsigned int x=0; x<xSize; x++)
        //for(unsigned int y=0; y<ySize; y++)
        {
            // Normalizar as coordenadas x e y
            float normalizedX = (static_cast<float>(x)*xScaleFactor) - 1.0;
            float normalizedY = (static_cast<float>(y)*yScaleFactor) - 1.0;

            // Gerar o raio para este pixel
            sceneCamera.generateRay(normalizedX, normalizedY, cameraRay);

            // TODO: posteriormente subtituir por um sistema de deteccao de colisoes
            // Testar interseccao com todos os objetos da cena
            std::shared_ptr<GeometricObject> closestObject;
            Vec3f closestIntersectionPoint, closestLocalNormal, closestLocalColor;
            double minDist = 1e6;
            bool intersectionFound = false;
            for(auto currentObject : this->sceneObjectList)
            {
                bool validIntersection = currentObject->testIntersection(cameraRay, intPoint, localNormal, localColor);
                if(validIntersection)
                {
                    // Setar flag para indicar que uma interseccao foi encontrada
                    intersectionFound = true;

                    // Calcular a distancia entre a camera e o ponto de interseccao
                    double dist = (intPoint - cameraRay.orig).norm();

                    // Se este objeto estiver mais proximo da camera do que os que verificamos antes, entao guardamos uma referencia a ele
                    if(dist < minDist)
                    {
                        minDist = dist;
                        closestObject = currentObject;
                        closestIntersectionPoint = intPoint;
                        closestLocalNormal = localNormal;
                        closestLocalColor = localColor;
                    }
                }
            }
            
            // Calcular a iluminacao para o objeto mais proximo, assumindo que exista uma interseccao valida
            if(intersectionFound)
            {
                // Calcular a intensidade da iluminacao
                float intensity;
                Color3f color;
                float red = 0.0, green = 0.0, blue = 0.0;
                bool validIllum = false;
                bool illumFound = false;
                for(auto currentLight : this->sceneLightList)
                {
                    validIllum = currentLight->computeIllumination(closestIntersectionPoint, closestLocalNormal, this->sceneObjectList, closestObject, color, intensity);
                    if(validIllum)
                    {
                        illumFound = true;
                        red += color[0]*intensity;
                        green += color[1]*intensity;
                        blue += color[2]*intensity;

                        if((ySize - y -1)*xSize + x == 115520)
                        {
                            std::clog << "Pos xy [" << x << "," << y << "] - Red green blue :" << red << "," << green << "," << blue << "\n";                            
                        }
                    }
                }
                
                if(illumFound)
                {
                    red *= closestLocalColor[0];
                    green *= closestLocalColor[1];
                    blue *= closestLocalColor[2];
                    imgBuffer.at((ySize - y - 1)*xSize + x)[0] = red;
                    imgBuffer.at((ySize - y - 1)*xSize + x)[1] = green;
                    imgBuffer.at((ySize - y - 1)*xSize + x)[2] = blue;
                    //std::clog << "-><-\n";
                    //outputImage.pixelData.at((ySize - y - 1)*xSize + x) = Color3f{red, green, blue};
                    //outputImage.pixelData.at((ySize - y - 1)*xSize + x).setPixelRGB(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue));
                    //outputImage.pixelData.at((ySize - y -1)*xSize + x).setPixelRGB(static_cast<uint8_t>(localColor[0]*intensity), static_cast<uint8_t>(localColor[1]*intensity), static_cast<uint8_t>(localColor[2]*intensity));
                }
            }
        }
    }

    std::clog << "Cores da esfera do meio = " << this->sceneObjectList.at(1)->baseColor << "\n";
    std::clog << "ImgBuffer[115520] na cena = " << imgBuffer.at(115520) << "\n";
    // Passar o buffer da imagem para o objeto responsavel
    outputImage.bufferToImageFormat(imgBuffer);    

    //std::clog << "Minimun distance: " << minDist << "  Maximun distance: " << maxDist << "\n";
    duration = std::chrono::high_resolution_clock::now() - stamp;
    std::cout << "\tTempo gasto para renderizar a cena: " << duration.count() << " s\n";

    return true;
}
 */