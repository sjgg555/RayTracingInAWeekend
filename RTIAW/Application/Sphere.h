#pragma once
#include "stdafx.h"
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere(Point3 cen, float r, std::shared_ptr<Material> mat)
		: m_centre(cen), m_radius(r), m_material(mat)
	{};
	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

private:
	Point3 m_centre;
	float m_radius;
	std::shared_ptr<Material> m_material;

};

bool Sphere::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	vec3 oc = r.origin() - m_centre;
	auto a = glm::length2(r.direction());
	auto b_half = dot(oc, r.direction());
	auto c = glm::length2(oc) - m_radius * m_radius;

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
	vec3 outward_normal = (rec.p - m_centre) / m_radius;
	rec.SetFaceNormal(r, outward_normal);
	rec.material = m_material;

	return true;
}
