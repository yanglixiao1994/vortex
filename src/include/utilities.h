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

template <typename T>
class RGB {
public:
	RGB(T rr = 0, T gg = 0, T bb = 0) :r{ rr }, g{ gg }, b{ bb } {}
	T r, g, b;
	RGB operator+(const RGB&c) { return RGB(this->r + c.r, this->g + c.g, this->b + c.b); };
	RGB& operator+=(const RGB&c) { this->r += c.r; this->g += c.g; this->b += c.b; return *this; }
	RGB& operator/=(T n) { this->r /= n; this->g /= n; this->b /= n; return *this; }
};
using vec3f = vec3<float>;
using vec3i = vec3<int>;
using vec2f = vec2<float>;
using vec2i = vec2<int>;
using RGBF = RGB<float>;
using RGB8I = RGB<uint8>;

template<>
class RGB<uint8> {
public:
	RGB(uint8 rr = 0, uint8 gg = 0, uint8 bb = 0) :r{ rr }, g{ gg }, b{ bb } {}
	uint8 r, g, b;
	RGB operator+(const RGB&c) { return RGB(this->r + c.r, this->g + c.g, this->b + c.b); };
	RGB& operator+=(const RGB&c) { this->r += c.r; this->g += c.g; this->b += c.b; return *this; }
	RGB& operator=(const RGB<float>&c) {
		r = c.r * 255;
		g = c.g * 255;
		b = c.b * 255;
		return *this;
	}
};
