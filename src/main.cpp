#pragma warning(disable:4996)
#include "include/sample.h"
#include "include/scene.h"
#include "include/SDF.h"
int main()
{
	Scene s;
	s.setCanvas(1024, 1024);
	s.setSampleMethod(ESampleMethod::Jettered, 1024,100,16);
	s.sdfs.push_back(std::make_shared<CircleSDF>(CircleSDF(200, 300, 100, RGBF{ 1.f,0.f,0.f })));
	s.sdfs.push_back(std::make_shared<CircleSDF>(CircleSDF(500, 300, 100, RGBF{ 0.f,1.f,0.f })));
	s.sdfs.push_back(std::make_shared<CircleSDF>(CircleSDF(700, 300, 100, RGBF{ 0.f,0.f,1.f })));
	s.render();
	s.saveToPNG("basic.png");
	return 0;
}
