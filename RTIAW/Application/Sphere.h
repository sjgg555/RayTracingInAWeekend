#pragma once
#include "stdafx.h"
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere(Point3 cen, float r)
		: centre(cen), radius(r)
	{};
	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

private:
	Point3 centre;
	float radius;
};

bool Sphere::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	vec3 oc = r.origin() - centre;
	auto a = glm::length2(r.direction());
	auto b_half = dot(oc, r.direction());
	auto c = glm::length2(oc) - radius * radius;

	auto discriminant = b_half * b_half - a * c;
	if (discriminant < 0) 
		return false;
	auto sqrt_d = glm::sqrt(discriminant);

	auto root = (-b_half - sqrt_d) / a;
	if (root < t_min || root > t_max)
	{
		root = (-b_half + sqrt_d) / a;
		if (root < t_min || root > t_max)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - centre) / radius;
	rec.SetFaceNormal(r, outward_normal);

	return true;
}
