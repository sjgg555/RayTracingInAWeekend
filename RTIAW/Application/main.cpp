#include "stdafx.h"
#include "Ray.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"

#include <iostream>

float hit_sphere(const point3& centre, float radius, const Ray& r) 
{
	vec3 oc = r.origin() - centre;
	auto a = glm::length2(r.direction());
	auto half_b = dot(oc, r.direction());
	auto c = glm::length2(oc) - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
	{
		return -1.0f;
	}
	else
	{
		return (-half_b - sqrt(discriminant)) / a;
	}
}

color ray_color(const Ray& r, const Hittable& world)
{
	hit_record rec;
	if (world.hit(r, 0, infinity, rec))
	{
		return 0.5f * (rec.normal + color(1, 1, 1));
	}
	vec3 unit_direction(glm::normalize(r.direction()));
	auto t = 0.5f * (unit_direction.y + 1.0f);
	return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + (t * color(0.5f, 0.7f, 1.0f));
}

int main()
{
	const auto aspect_ratio = 16.0f / 9.0f;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	HittableList world;
	world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
	world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

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
			color pixel_color = ray_color(r, world);
			write_color(std::cout, pixel_color);
		}
	}

	std::cerr << "\nDone.\n";
}