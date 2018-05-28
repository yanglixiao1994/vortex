#include "scene.h"
#include <type_traits>
#include <functional>


/**March return a nearest surface color*/
color scene::march(const vec2f&pos, const vec2f&dir) {
	float nearest = 1e10;
	color result{0.f,0.f};
	for (const auto&sdf : sdfs) {
		float dist = sdf->getDist(pos.x, pos.y);
		while(dist > EPISILON && dist < sqrtf(_width * _width + _height * _height)) {
			dist += sdf->getDist(pos.x + dir.x * dist, pos.y + dir.y * dist);
		}
		if (dist < nearest) {
			nearest = dist;
			result = sdf->color;
		}
	}
	return result;
}

std::list<color> scene::render() {
	std::list<color> pic;
	color tmp{ 0.f,0.f };
	for (uint16 H = 0; H < _height; ++H) {
		for (uint16 W = 0; W < _width; ++W) {
			pic.push_back(samplefunc(vec2f{ H,W }, _samples));
		}
	}
	return pic;
}
