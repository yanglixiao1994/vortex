#pragma once
#include "utilities.h"
/**
	Signed Distance Field is a function float F(vec2 pos)
	It receives a position in a specified scene,and it return a distance to the SDF surface.
*/
class SDF {
public:
	uint16 x, y;
	RGBF diffuse;
	SDF(uint16 px = 0, uint16 py = 0, const RGBF&diff = RGBF(1.f, 1.f, 1.f)) :x{ px }, y{ py }, diffuse{diff} {};
	virtual float getDist(float x, float y) = 0;
};

class CircleSDF :public SDF {
public:
	float radius;
	CircleSDF(uint16 px, uint16 py, uint16 radius = 0, const RGBF&diffuse = RGBF{1.f,1.f,1.f}) :radius(radius), SDF(px, py, diffuse) {}
	float getDist(float px,float py) override {
		return std::fabsf(std::sqrtf((px - x)*(px - x) + (py - y) * (py - y)) - radius);
	}
};
