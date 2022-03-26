#include "stdafx.h"
#include "Ray.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Utilities.h"
#include "Camera.h"

#include <iostream>

float HitSphere(const Point3& centre, float radius, const Ray& r) 
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

Color GetRayColor(const Ray& r, const Hittable& world)
{
	HitRecord rec;
	if (world.Hit(r, 0, infinity, rec))
	{
		return 0.5f * (rec.normal + Color(1, 1, 1));
	}
	vec3 unit_direction(glm::normalize(r.direction()));
	auto t = 0.5f * (unit_direction.y + 1.0f);
	return (1.0f - t) * Color(1.0f, 1.0f, 1.0f) + (t * Color(0.5f, 0.7f, 1.0f));
}

int main()
{
	const auto aspect_ratio = 16.0f / 9.0f;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;

	HittableList world;
	world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
	world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

	Camera cam(aspect_ratio);

	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
		for (int i = 0; i < image_width; ++i)
		{ 
			Color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++)
			{
				auto u = float(i + Utilities::RandomFloat()) / (image_width - 1);
				auto v = float(j + Utilities::RandomFloat()) / (image_height - 1);
				Ray r = cam.GetRay(u, v);
				pixel_color += GetRayColor(r, world);
			}
			Utilities::WriteColor(std::cout, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "\nDone.\n";
}