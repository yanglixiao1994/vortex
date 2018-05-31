#pragma once

#include<list>
#include<vector>
#include<memory>
#include<functional>
#include"SDF.h"
#include"utilities.h"

enum class ESampleMethod :uint8 {
	Random,
	stratified,
	Jettered
};

class Scene {
public:
	std::list<std::shared_ptr<SDF>>sdfs;

public:
	pic render();
	void setSampleMethod(const ESampleMethod&sm = ESampleMethod::Jettered, uint16 samples = 64);
	void setCanvas(uint16 width = 512, uint16 height = 512) { _width = width; _height = height;  };
private:
	color march(const vec2i&pos, const vec2f&dir); 

private:
	std::function < color(const vec2i &pos) > sample;
	uint16 _width;
	uint16 _height;
};
