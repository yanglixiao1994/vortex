#include"include/utilities.h"
#include "include/svpng.h"
#pragma warning(disable:4996)
void pic::saveToPNG(const std::string&file){
	svpng(fopen(file.c_str(), "wb"), width, height, (const unsigned char *)(&data[0]), 0);
}