#pragma once

#include<list>
#include<memory>
#include<functional>
#include"SDF.h"
#include"RenderMath.h"

enum class ESampleMethod :uint8 {
	Random,
	stratified,
	Jettered
};
class scene {
public:
	std::list<std::shared_ptr<SDF>>sdfs;
	std::list<color> render();
	void setSampleMethod(const ESampleMethod&sm = ESampleMethod::Jettered, uint16 samples = 64);
	void setCanvas(uint16 width = 512, uint16 height = 512) { _width = width; _height = height;  };
private:
	color march(const vec2f&pos, const vec2f&dir); 
	std::function < color(const vec2f &pos) > samplefunc;

	uint16 _width;
	uint16 _height;
};