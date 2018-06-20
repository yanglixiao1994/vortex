#pragma once

#include <math.h>
#include <random>

constexpr float PI = 3.1415926f;
constexpr float MINFLOAT = 1e-5f;
constexpr float MAXFLOAT = 1e20f;
/**Produce the Randoms*/
float rand_Uniform(float min, float max);
int rand_Uniform(int min, int max);