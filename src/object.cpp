#include "include/object.h"
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

float Polygon::calc_dist(const vec2f&p) {

}