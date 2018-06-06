#pragma warning(disable:4996)
#include "include/sample.h"
#include "include/scene.h"
#include "include/SDF.h"
int main()
{
	Scene s;
	s.setCanvas(1000, 1000);
	s.setSampleMethod(ESampleMethod::Jettered, 512,8,8);
	s.setAttenuation(false);
	for (int i = 0; i < 20; i++) {
		s.sdfs.push_back(std::make_shared<CircleSDF>(CircleSDF(rand_Uniform(50,950), rand_Uniform(50, 950), rand_Uniform(10, 50), RGBF{ rand_Uniform(0.f,1.f),rand_Uniform(0.f,1.f),rand_Uniform(0.f,1.f) })));
	}
	//s.sdfs.push_back(std::make_shared<CircleSDF>(CircleSDF(200, 300, 100, RGBF{ 1.f,0.f,0.f })));
	//s.sdfs.push_back(std::make_shared<CircleSDF>(CircleSDF(500, 300, 100, RGBF{ 0.f,1.f,0.f })));
	//s.sdfs.push_back(std::make_shared<CircleSDF>(CircleSDF(700, 300, 100, RGBF{ 0.f,0.f,1.f })));
	s.render();
	s.saveToPNG("basic.png");
	return 0;
}
