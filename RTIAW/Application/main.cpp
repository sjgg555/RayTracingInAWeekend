#include "stdafx.h"
#include "Ray.h"

#include <iostream>

bool hit_sphere(const point3& centre, float radius, const Ray& r) 
{
	vec3 oc = r.origin() - centre;
	auto a = dot(r.direction(), r.direction());
	auto b = 2.0f * dot(oc, r.direction());
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = (b * b) - (4 * a * c);
	return (discriminant > 0);
}

color ray_color(const Ray& r)
{
	if (hit_sphere(point3(0,0,-1), 0.5, r))
	{
		return color(1, 0, 0);
	}
	vec3 unit_direction(glm::normalize(r.direction()));
	float t = 0.5f * (unit_direction.y + 1.0);
	return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + (t * color(0.5f, 0.7f, 1.0f));
}

void write_color(std::ostream& out, color pixel_color) 
{
	//Write the translated color [0,255] value of each color component;
	out << static_cast<int>(255.999 * pixel_color.x) << " "
		<< static_cast<int>(255.999 * pixel_color.y) << " "
		<< static_cast<int>(255.999 * pixel_color.z) << "\n";
}

int main()
{
	const auto aspect_ratio = 16.0f / 9.0f;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);


	auto viewport_height = 2.0f;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0f;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - (horizontal / 2.0f) - (vertical / 2.0f) - vec3(0, 0, focal_length);

	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
		for (int i = 0; i < image_width; ++i)
		{ 
			auto u = float(i) / (image_width - 1);
			auto v = float(j) / (image_height - 1);
			Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
		}
	}

	std::cerr << "\nDone.\n";
}