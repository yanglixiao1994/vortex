#include "include/scene.h"
#include<iostream>


/**Return the color of the nearest surface in a direction.*/
color Scene::march(const vec2i&pos, const vec2f&dir) {
	float nearest = sqrtf(_width * _width + _height * _height);
	color result{0.f,0.f};
	for (const auto&sdf : sdfs) {
		float dist = sdf->getDist(pos.x, pos.y);
		float step = 1.f;
		int steps = 0;
		while(step > EPISILON && dist < nearest && steps < 100) {
			step = sdf->getDist(pos.x + dir.x * dist, pos.y + dir.y * dist);
			dist += step;
			steps++;
			//std::cout << step << std::endl;
		}
		if (dist < nearest) {
			nearest = dist;
			result = sdf->diffuse;
		}
	}
	return result;
}
/**Sample every pixel and return the result in pic*/
pic Scene::render() {
	pic p{ _width,_height,std::vector<color>(_width * _height) };
	for (uint16 H = 0; H < _height; ++H) {
		for (uint16 W = 0; W < _width; ++W) {
			p._data[W + H * _width] = sample(vec2i{ H,W });
		}
	}
	return p;
}
void Scene::setSampleMethod(const ESampleMethod&sm, uint16 samples) {
	switch (sm) {
	case ESampleMethod::Random:
		sample = [samples,this](const vec2i&pos)->color {
			color result;
			for (uint16 i = 0; i < samples; ++i) {
				float theta = 2 * PI * rand_Uniform(0.f, 1.f);
				float dx = cosf(theta);
				float dy = sinf(theta);
				result += march(pos, vec2f{ dx,dy });
			}
			if (result.g > 30.f) {
				std::sin(result.b);
			}
			return result/=samples;
		};
		break;
	case ESampleMethod::stratified:
		sample = [samples, this](const vec2i&pos)->color {
			color result;
			for (uint16 i = 0; i < samples; ++i) {
				float theta = 2 * PI * i / samples;
				float dx = cosf(theta);
				float dy = sinf(theta);
				result = march(pos, vec2f{ dx,dy });
			}
			return result /= samples;
		};
		break;
	case ESampleMethod::Jettered:
		sample = [samples, this](const vec2i&pos)->color {
			color result;
			for (uint16 i = 0; i < samples; ++i) {
				float deno = 1 / (float)samples;
				float theta = 2 * PI * (i * deno + deno * rand_Uniform(0.f, 1.f));
				float dx = cosf(theta);
				float dy = sinf(theta);
				result = march(pos, vec2f{ dx,dy });
			}
			return result /= samples;
		};
		break;
	}
}