#pragma once
#include "stdafx.h"
#include "Ray.h"
#include "Utilities.h"

class Material;

struct HitRecord
{
	Point3 p;
	vec3 normal;
	float t;
	bool front_face;
	std::shared_ptr<Material> material;

	inline void SetFaceNormal(const Ray& r, const vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal);
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class Hittable
{
public:
	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

