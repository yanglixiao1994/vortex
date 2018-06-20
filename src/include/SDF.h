#pragma once
#include "object.h"
/**
	Signed Distance Field is a function float F(vec2 pos)
	It receives a position in a specified scene,and it return a distance to the SDF surface.
*/

namespace vortex {

	class DiscreteSDF :public Object {
	public:
		RGBF diffuse;
		DiscreteSDF(uint16 px = 0, uint16 py = 0, const RGBF&diff = RGBF(1.f, 1.f, 1.f)) :x{ px }, y{ py }, diffuse{ diff } {};
		virtual float getDist(float x, float y) = 0;

	private:
		uint16 _count;
		
	};

	class CircleSDF :public SDF {
	public:
		float radius;
		CircleSDF(uint16 px, uint16 py, uint16 radius = 0, const RGBF&diffuse = RGBF{ 1.f,1.f,1.f }) :radius(radius), SDF(px, py, diffuse) {}
		float getDist(float px, float py) override {
			return std::fabsf(std::sqrtf((px - x)*(px - x) + (py - y) * (py - y)) - radius);
		}
	};
}