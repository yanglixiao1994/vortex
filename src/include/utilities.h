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
	T x, y;
	vec2() { x = y = 0; }
	vec2(T xx, T yy) :x(xx), y(yy) {}
	bool HasNaNs()const { return isNaN(x) || isNaN(y); }
	vec2(const vec2<T>&v) {
		x = v.x;
		y = v.y;
	}
	vec2<T> &operator=(const vec2<T>&v) {
		x = v.x;
		y = v.y;
		return *this;
	}
	vec2<T> operator+(const vec2<T>&v)const {
		return vec2(x + v.x, y + v.y);
	}
	vec2<T> &operator+=(const vec2<T>&v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	vec2<T> operator-(const vec2<T>&v)const {
		return vec2(x - v.x, y - v.y);
	}
	vec2<T> &operator-=(const vec2<T>&v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	bool operator==(const vec2<T>&v)const { return x == v.x && y == v.y; }
	bool operator!=(const vec2<T>&v)const { return x != v.x || y != v.y; }
	template <typename U>
	vec2<T> operator*(U u)const {
		return vec2<T>(x * u, y * u);
	}
	template <typename U>
	vec2<T>& operator*=(U u) {
		x *= u;
		y *= u;
		return *this;
	}
	template <typename U>
	vec2<T> operator/(U u)const {
		float div = (Float)1 / u;
		return vec2<T>(x * div, y * div);
	}
	template <typename U>
	vec2<T>& operator/=(U u) {
		float div = (Float)1 / u;
		x *= div;
		y *= div;
		return *this;
	}
	vec2<T> operator-()const {
		return vec2(-x, -y);
	}
	void Normalize() {
		double l = Length();
		x /= l;
		y /= l;
	}
	T Dot(const vec2<T>&v)const {
		return x * v.x + y * v.y;
	}
	T operator[](int i) const {
		if (i == 0)return x;
		else return y;
	}
	float LengthSquared()const { return x * x + y * y; }
	float Length()const { return std::sqrt(LengthSquared()); }
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
	RGB operator*(const RGB&c) { 
		return RGB(this->r * c.r, this->g * c.g, this->b * c.b); 
	}
	RGB operator*(float c) {
		return RGB(this->r * c, this->g * c, this->b * c);
	}
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
