#include "scene.h"
#include <type_traits>
#include <functional>


/**Return the color of the nearest surface in a direction.*/
color scene::march(const vec2f&pos, const vec2f&dir) {
	float nearest = 1e10;
	color result{0.f,0.f};
	for (const auto&sdf : sdfs) {
		float dist = sdf->getDist(pos.x, pos.y);
		float step = 0.f;
		while(std::abs(step) > EPISILON && dist < sqrtf(_width * _width + _height * _height)) {
			step = sdf->getDist(pos.x + dir.x * dist, pos.y + dir.y * dist);
			dist += step;
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
			pic.push_back(samplefunc(vec2f{ H,W }));
		}
	}
	return pic;
}

void scene::setSampleMethod(const ESampleMethod&sm, uint16 samples) {
	switch (sm) {
	case ESampleMethod::Random:
		samplefunc = [samples,this](const vec2f&pos)->color {
			color result;
			for (uint16 i = 0; i < samples; ++i) {
				float theta = 2 * PI * rand_Uniform(0.f, 1.f);
				float dx = cosf(theta);
				float dy = sinf(theta);
				result = march(pos, vec2f{ dx,dy });
			}
			return result/=samples;
		};
	case ESampleMethod::stratified:
		samplefunc = [samples, this](const vec2f&pos)->color {
			color result;
			for (uint16 i = 0; i < samples; ++i) {
				float theta = 2 * PI * i / samples;
				float dx = cosf(theta);
				float dy = sinf(theta);
				result = march(pos, vec2f{ dx,dy });
			}
			return result /= samples;
		};
	case ESampleMethod::Jettered:
		samplefunc = [samples, this](const vec2f&pos)->color {
			color result;
			for (uint16 i = 0; i < samples; ++i) {
				float deno = 1 / samples;
				float theta = 2 * PI * (i * deno + deno * rand_Uniform(0.f, 1.f));
				float dx = cosf(theta);
				float dy = sinf(theta);
				result = march(pos, vec2f{ dx,dy });
			}
			return result /= samples;
		};
	}
}