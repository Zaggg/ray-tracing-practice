#pragma once
#include "ray.h"

class camera
{
public:
	camera();
	// @vfov degree from two border plane
	// @aspect ����������
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect)
	{
		vec3 u, v, w;
		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = vec3(-half_width, -half_height, -1.0);
		lower_left_corner = origin - half_width * u - half_height * v - w;
		horizontal = 2 * half_width * u;
		vertical = 2 * half_height * v;
	}
	~camera()=default;

	ray get_ray(float u, float v);

	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;
};

