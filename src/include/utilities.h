#pragma once
#include <vector>
#include "RenderMath.h"
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long int;

template <typename T>
class vec2 {
public:
	vec2(T xx = 0, T yy = 0) :x{ xx }, y{ yy } {}
	T x, y;
};

template <typename T>
class vec3 {
public:
	vec3(T xx = 0, T yy = 0, T zz = 0) :x{ xx }, y{ yy }, z{ zz } {}
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
using vec3i = vec3<int>;
using vec2f = vec2<float>;
using vec2i = vec2<int>;

struct pic {
	pic(uint16 W, uint16 H, std::vector<color>D)
		:width{ W }, height{ H }, _data{ D } {
		_data.reserve(width * height);
	};
	void saveToPNG(const std::string&);
	uint16 width;
	uint16 height;
	std::vector<color>_data;
};