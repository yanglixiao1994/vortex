#pragma once

#include "RenderMath.h"
#include "trace.h"
#include<functional>
enum class ESampleMethod :uint8{
	Random,
	stratified,
	Jettered
};

float sampleRandom(const vec2f&pos,int samples)
{
	float sum = 0.f;
	for (int i = 0; i < samples; i++) {
		float dx = rand_Uniform(-1.f, 1.f);
		float dy = sqrtf(1 - dx * dx);
		sum += March(x, y, dx, dy);
	}
	return sum;
}

