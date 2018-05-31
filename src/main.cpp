#pragma warning(disable:4996)
#include "include/sample.h"
#include "include/scene.h"
#include "include/SDF.h"
int main()
{
	Scene s;
	s.setCanvas(512, 512);
	s.setSampleMethod(ESampleMethod::Random, 32);
	s.sdfs.push_back(std::make_shared<CircleSDF>(CircleSDF(100, 200, 50, color{0.f,1.f,0.f})));
	s.render().saveToPNG("basic.png");
	return 0;
}
