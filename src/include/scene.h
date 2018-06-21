#pragma once

#include<list>
#include<vector>
#include<memory>
#include<functional>
#include<future>
#include"Object.h"
#include"utilities.h"
namespace vortex {
	enum class ESampleMethod :uint8 {
		Random,
		stratified,
		Jettered
	};

	class Scene {
	public:
		std::list<std::shared_ptr<Object>>sdfs;

	public:
		void render();
		void setSampleMethod(const ESampleMethod&sm = ESampleMethod::Jettered, uint16 samples = 64, uint16 steps = 100, uint8 threads = 8);
		void setCanvas(uint16 width = 512, uint16 height = 512);
		void setAttenuation(bool att) {
			attenuation = att;
		}
		void drawPoint(const vertex&);
		void drawLineSeg(const lineseg&);
		void saveToPNG(const std::string&);
	private:
		RGBF march(const vec2i&pos, const vec2f&dir);

	private:
		std::vector<std::future<bool>>_threads;
		std::vector<RGBF>_rendertarget_RGB_32F;
		std::vector<RGB8I>_rendertarget_RGB_8I;
		std::function<RGBF(const vec2i &pos)>sample;
		uint16 _steps;
		uint16 _width;
		uint16 _height;
		bool attenuation;
	};
}