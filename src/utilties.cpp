#include"include/utilities.h"
#include "include/svpng.h"
#pragma warning(disable:4996)
void pic::saveToPNG(const std::string&file){
	uint8 *temp = new uint8[width * height * 3];
	int count = 0;
	for (const auto&x : _data) {
		if (x.g > .1f) {
			std::sin(x.g);
		}
		temp[count] = x.r * 255;
		temp[count + 1] = x.g * 255;
		temp[count + 2] = x.b * 255;
		count += 3;
	}
	svpng(fopen(file.c_str(), "wb"), width, height, temp, 0);
	delete []temp;
}