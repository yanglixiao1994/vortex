#pragma once
#include "RenderMath.h"
#include <iostream>
float March(float x, float y, float dx, float dy)
{
	float t = .0f;// = circleSDF(x, y, .7, .7, .1);

	if (t < .05f && t > .01f)
		return t;
	else return 0.f;
}

