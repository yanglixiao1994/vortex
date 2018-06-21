#include "include/object.h"
#include "external/Eigen/Dense"
using namespace vortex;
//Gather operator ,can be parallelized.Reduce.
vec2f Polygon::calc_center(){
	vec2f center{0,0};
	for (const auto&x : vertexs) {
		center += x.posi;
	}
	_center /= vertexs.size();
	return _center;
}

//TODO:Use more accurate boundary to represent the closure.For now,AABB.
void Polygon::calc_closure() {
	float xmin = MAXFLOAT, xmax = MINFLOAT, ymin = MAXFLOAT, ymax = MINFLOAT;
	for (const auto&x : vertexs) {
		xmin = xmin < x.posi.x ? xmin : x.posi.x;
		xmax = xmax > x.posi.x ? xmax : x.posi.x;
		ymin = ymin < x.posi.y ? ymin : x.posi.y;
		ymin = ymin > x.posi.y ? ymin : x.posi.y;
	}
	_closure.clear();
	_closure.push_back(vec2f{ xmin,ymin });
	_closure.push_back(vec2f{ xmax,ymin });
	_closure.push_back(vec2f{ xmax,ymax });
	_closure.push_back(vec2f{ xmin,ymax });
}


/**The two line segments intersection problem is actually a 2 * 2 linear system.
	It can be solved by the Cramer's rule.
	Reference:https://en.wikipedia.org/wiki/Cramer%27s_rule
*/
float Polygon::calc_dist(const vec2f&p,const vec2f&dir) {

	float min_distance = MAXFLOAT;
	for (auto i = vertexs.begin();;) {
		auto oldptr = i;
		++i;

	}

}
/**
I adopted a cornel cutting method. 
You can find alternative ways in :
http://graphics.stanford.edu/courses/cs468-10-fall/LectureSlides/10_Subdivision.pdf
Time complexity:O(N)
Space complexity:
GPU Accerlator:No
Unit Test:No
*/
void Polygon::subdivsion(int degree) {
	//add assistant points
	for (auto i = vertexs.begin(); i != vertexs.end();) {
		auto oldptr = i;
		++i;
		if (i == vertexs.end()) {
			vec2f p1 = linearInterpolation(oldptr->posi, vertexs.front().posi, 0.25);
			vec2f p2 = linearInterpolation(oldptr->posi, vertexs.front().posi, 0.75);
			vertex v1{ p1,oldptr->color,oldptr->mass / 2 };
			vertex v2{ p2,vertexs.front().color,vertexs.front().mass / 2 };
			vertexs.insert(vertexs.insert(vertexs.begin(), v2), v1);
			break;
		}
		vec2f p1 = linearInterpolation(oldptr->posi, i->posi, 0.25);
		vec2f p2 = linearInterpolation(oldptr->posi, i->posi, 0.75);

		vertex v1{ p1,oldptr->color,oldptr->mass / 2 };
		vertex v2{ p2,i->color,i->mass / 2 };
		vertexs.insert(vertexs.insert(i, v2), v1);
	}
	//delete old cornel points
	int count = 0;
	for (auto i = vertexs.begin();;) {
		if (count % 3 == 0) {
			i = vertexs.erase(i);
		}
		else {
			++i;
			++count;
		}
	}
}