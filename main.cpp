#pragma warning(disable:4996)
#include "svpng.h"
#include "sample.h"
#include "SDF.h"
#include <math.h>
constexpr int W = 512;
constexpr int H = 512;
unsigned char img[W * H * 3];
int main()
{
	CircleSDF c(.1f, .3f, .3f);
	unsigned char*p = img;
	for (int y = 0; y < H; y++)
		for (int x = 0; x < W; x++) {
			int tmp = (int)(fminf(sampleRandom((float)x / W, (float)y / H, 10) *255.0f, 255.0f));
			p[0 + x * 3 + y * W * 3] = p[1 + x * 3 + y * W * 3] = p[2 + x * 3 + y * W * 3] = tmp;
		}
	svpng(fopen("basic.png", "wb"), W, H, img, 0);
	return 0;
}
