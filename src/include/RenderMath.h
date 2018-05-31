#pragma once

#include <math.h>
#include <random>
constexpr float PI = 3.1415926;
constexpr float EPISILON = 1e-10;
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long int;


template <typename T>
class vec2 {
public:
	vec2(T xx = 0, T yy = 0) :x{ xx }, y{ yy }{}
	T x, y;
};

template <typename T>
class vec3 {
public:
	vec3(T xx = 0,T yy = 0,T zz = 0):x{xx},y{yy},z{zz}{}
	T x, y, z;
};

class color {
public:
	color(float rr = 0, float gg = 0, float bb = 0) :r{ rr }, g{ gg }, b{ bb } {}
	float r, g, b;
	color operator+(const color&c) { return color(this->r + c.r, this->g + c.g, this->b + c.b); };
	color& operator+=(const color&c) { this->r += c.r; this->g += c.g; this->b += c.b; return *this; }
	color& operator/=(uint32 n) { this->r /= n; this->g /= n; this->b /= n; return *this; }
};

using vec3f = vec3<float>;
using vec2f = vec2<float>;
/**Produce the Randoms*/
float rand_Uniform(float min, float max);
int rand_Uniform(int min, int max);