#pragma once
#include "utilities.h"
#include <list>
#include <memory>
//Object is the basic class in engine,it can be rendered,emit the light.
namespace vortex {
	
	struct vertex {
		vec2f posi;
		RGBF color;
		float mass;
	};
	struct lineseg {
		vertex start;
		vertex end;
	};

	class Object {
	public:
		virtual void translate(const vec2f&v) = 0;
		virtual void rotate(float) = 0;
		virtual void scale(const vec2f&v) = 0;
		virtual bool in(const vec2f&p) = 0;
		//degree is the number of interpolation points.
		virtual void subdivsion(int degree) = 0;
		virtual vec2f calc_center() = 0;
		virtual float calc_dist(const vec2f&p,const vec2f&dir) = 0;
		virtual void calc_closure() = 0;
	protected:
		vec2f _center;
		std::list<Object*>_childs;
		std::list<vec2f>_closure;
	};
	class Polygon :public Object {
	private:
		std::list<vertex>vertexs;
	public:
		virtual void translate(const vec2f&v)override;
		virtual void rotate(float)override;
		virtual void scale(const vec2f&v)override;
		virtual bool in(const vec2f&p)override;
		//degree is the number of interpolation points.
		virtual void subdivsion(int degree)override;
		virtual vec2f calc_center()override;
		virtual float calc_dist(const vec2f&p,const vec2f&dir)override;
		virtual void calc_closure()override;
	};
}