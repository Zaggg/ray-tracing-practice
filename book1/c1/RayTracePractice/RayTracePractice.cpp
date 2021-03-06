// RayTracePractice.cpp: 定义控制台应用程序的入口点。
//
#include "ppm2png.h"


int main()
{
	int nx = 200;
	int ny = 100;
	ppm2png png;
	std::vector<RGB> image;

	for(int j=ny-1;j>=0;j--)
		for (int i = 0; i < nx; i++)
		{
			RGB rgb;
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;
			rgb.r = int(255.99*r);
			rgb.g = int(255.99*g);
			rgb.b = int(255.99*b);
			image.push_back(rgb);
		}

	png.get_image(image, nx, ny);
    return 0;
}

