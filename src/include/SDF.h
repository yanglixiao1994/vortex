#pragma once
#include "RenderMath.h"
/**
	Signed Distance Field is a function float F(vec2 pos)
	It receives a position in a specified scene,and it return a distance to the SDF surface.
*/
class SDF {
public:
	float x, y;
	color color;
	SDF(float px = 0,float py = 0) :x{ px }, y{ py } {};
	virtual float getDist(float x, float y) = 0;
};

class CircleSDF :public SDF {
public:
	float radius;
	CircleSDF(float px,float py,float radius = 0) :radius(radius) ,SDF(px,py){}
	float getDist(float px, float py) override {
		return sqrtf((px - x)*(px - x) + (py - y) * (py - y)) - radius;
	}
};
