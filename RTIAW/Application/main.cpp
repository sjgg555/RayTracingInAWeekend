#pragma once
#include "stdafx.h"
#include "Ray.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Utilities.h"
#include "Camera.h"
#include "Material.h"

#include <iostream>
#include <string>
#include <fstream>

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

Color GetRayColor(const Ray& r, const Hittable& world, int depth)
{
	if (depth <= 0)
	{
		return Color(0, 0, 0);
	}
	HitRecord rec;
	if (world.Hit(r, 0.001f, infinity, rec))
	{
		Point3 target = rec.p + rec.normal + glm::normalize(Utilities::RandomVec3InHemi(rec.normal));
		return 0.5f * GetRayColor(Ray(rec.p, target - rec.p), world, depth - 1);
	}
	vec3 unit_direction(glm::normalize(r.direction()));
	auto t = 0.5f * (unit_direction.y + 1.0f);
	return (1.0f - t) * Color(1.0f, 1.0f, 1.0f) + (t * Color(0.5f, 0.7f, 1.0f));
}

int main(int argc, char* argv[])
{
	int samples_per_pixel = 10;
	int image_width = 400;
	if (argc == 3) 
	{
		samples_per_pixel = std::stoi(argv[1]);
		image_width = std::stoi(argv[2]);
	}

	const auto aspect_ratio = 16.0f / 9.0f;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int max_depth = 50;

	HittableList world;

	auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));

	world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));

	Camera cam(aspect_ratio);

	std::ofstream imageFile{ "image.ppm" };

	Utilities::WriteHeader(imageFile, image_width, image_height);

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
		for (int i{}; i < image_width; ++i)
		{ 
			Color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++)
			{
				auto u = float(i + Utilities::RandomFloat()) / (image_width - 1);
				auto v = float(j + Utilities::RandomFloat()) / (image_height - 1);
				Ray r = cam.GetRay(u, v);
				pixel_color += GetRayColor(r, world, max_depth);
			}
			Utilities::WriteColor(imageFile, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "\nDone.\n";
}