// RayTracePractice.cpp: 定义控制台应用程序的入口点。
//
#include "ppm2png.h"
#include "camera.h"
#include "sphere.h"
#include "hitable_list.h"
#include <float.h>
#include<random>
#include<functional>

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0, 1);
auto dice = std::bind(distribution, generator);

vec3 random_in_unit_sphere()
{
	vec3 p;
	do {
		p = 2.0*vec3(dice(), dice(), dice()) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1);
	return p;
}
vec3 color(const ray& r,hitable* world)
{
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec))
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5*color(ray(rec.p, target - rec.p),world);
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	}
}

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;
	ppm2png png;
	std::vector<RGB> image;
	
	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	camera cam;

	for(int j=ny-1;j>=0;j--)
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			RGB rgb;
			for (int s = 0; s < ns; s++)
			{
				float u = float(i+dice()) / float(nx);
				float v = float(j+dice()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			rgb.r = int(255.99*col[0]);
			rgb.g = int(255.99*col[1]);
			rgb.b = int(255.99*col[2]);
			image.push_back(rgb);
		}

	png.get_image(image, nx, ny);
    return 0;
}

