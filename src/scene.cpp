#include "include/scene.h"
#include "include/svpng.h"
#include<iostream>

void Scene::setCanvas(uint16 width, uint16 height) {
	_width = width; _height = height;
	_rendertarget_RGB_32F.resize(_width * _height);
	_rendertarget_RGB_8I.resize(_width * _height);
}
/**Return the RGB of the nearest surface in a direction.*/
RGBF Scene::march(const vec2i&pos, const vec2f&dir) {
	float nearest = sqrtf(_width * _width + _height * _height);
	float farnest = nearest;
	RGBF result{0.f,0.f};
	for (const auto&sdf : sdfs) {
		float dist = sdf->getDist(pos.x, pos.y);
		float step = 1.f;
		int steps = 0;
		while(step > EPISILON && dist < nearest && steps < _steps) {
			step = sdf->getDist(pos.x + dir.x * dist, pos.y + dir.y * dist);
			dist += step;
			steps++;
		}
		if (dist < nearest) {
			nearest = dist;
			if(attenuation)
				result = sdf->diffuse * (1 - dist / farnest);
			else result = sdf->diffuse;
		}
	}
	return result;
}
/**Sample every pixel and return the result in pic*/
void Scene::render() {
	int linesperthd = _height / _threads.size();
	for (int i = 0; i < _threads.size(); i++) {
		_threads[i] = std::async([linesperthd,i,this]()->bool {
			for (uint16 H = i * linesperthd; H < (i + 1) * linesperthd; ++H) {
				for (uint16 W = 0; W < _width; ++W) {
					_rendertarget_RGB_32F[W + H * _width] = sample(vec2i{ H,W });
					_rendertarget_RGB_8I[W + H * _width] = _rendertarget_RGB_32F[W + H * _width];
				}
			}
			return true;
		});
	}
}
void Scene::setSampleMethod(const ESampleMethod&sm, uint16 samples,uint16 steps,uint8 threads) {
	_threads.resize(threads);
	_steps = steps;
	switch (sm) {
	case ESampleMethod::Random:
		sample = [samples,this](const vec2i&pos)->RGBF {
			RGBF result;
			for (uint16 i = 0; i < samples; ++i) {
				float theta = 2 * PI * rand_Uniform(0.f, 1.f);
				float dx = cosf(theta);
				float dy = sinf(theta);
				result += march(pos, vec2f{ dx,dy });
			}
			return result/=samples;
		};
		break;
	case ESampleMethod::stratified:
		sample = [samples, this](const vec2i&pos)->RGBF {
			RGBF result;
			for (uint16 i = 0; i < samples; ++i) {
				float theta = 2 * PI * i / samples;
				float dx = cosf(theta);
				float dy = sinf(theta);
				result += march(pos, vec2f{ dx,dy });
				if (result.r > .2f && result.g > .2f) {
					std::sin(result.r);
				}
			}
			return result /= samples;
		};
		break;
	case ESampleMethod::Jettered:
		sample = [samples, this](const vec2i&pos)->RGBF {
			RGBF result;
			for (uint16 i = 0; i < samples; ++i) {
				float deno = 1 / (float)samples;
				float theta = 2 * PI * (i * deno + deno * rand_Uniform(0.f, 1.f));
				float dx = cosf(theta);
				float dy = sinf(theta);
				result += march(pos, vec2f{ dx,dy });
			}
			return result /= samples;
		};
		break;
	}
}

void Scene::saveToPNG(const std::string&file) {
	for (auto&result : _threads) {
		if (result.get() == false) {
			std::abort();
		}
	}
	svpng(fopen(file.c_str(),"wb"), _width, _height, (const uint8*)&_rendertarget_RGB_8I[0], 0);
}