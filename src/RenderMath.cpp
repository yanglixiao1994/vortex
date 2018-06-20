#include "include/RenderMath.h"

std::default_random_engine randEngine;

float rand_Uniform(float min, float max) {
	std::uniform_real_distribution<float> urd(min, max);
	return urd(randEngine);
}

int rand_Uniform(int min, int max) {
	std::uniform_int_distribution<> uid(min, max);
	return uid(randEngine);
}


