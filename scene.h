#pragma once

#include<list>
#include<memory>
#include<functional>
#include"sample.h"
#include"SDF.h"
#include"RenderMath.h"
class scene {
public:
	std::list<std::shared_ptr<SDF>>sdfs;
	std::list<color> render();
	void setSampleMethod(const ESampleMethod&sm = ESampleMethod::Jettered, uint32 samples = 64) { _smethod = sm; _samples = samples; };
	void setWindow(uint16 width = 512, uint16 height = 512) { _width = width; _height = height;  };
private:
	color march(const vec2f&pos, const vec2f&dir) {}; 
	std::function < color(const vec2f &pos, uint16 samples) > samplefunc;

	uint16 _width;
	uint16 _height;
	uint16 _samples;
	ESampleMethod _smethod;
};