#include "material.h"

vec3 material::reflect(const vec3 & v, const vec3 & n) const
{
	return v - 2 * dot(v, n)*n;
}
