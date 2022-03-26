#pragma once
#include "Hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable
{
public:
	HittableList() {};
	HittableList(std::shared_ptr<Hittable> object)
	{
		Add(object);
	}

	void Clear()
	{
		objects.clear();
	}

	void Add(std::shared_ptr<Hittable> object)
	{
		objects.push_back(object);
	}

	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

private:
	std::vector<std::shared_ptr<Hittable>> objects;
};

bool HittableList::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	HitRecord temp_rec;
	bool hit_confirmed = false;
	auto closest_so_far = t_max;

	for (const auto& object : objects)
	{
		if (object->Hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_confirmed = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_confirmed;
}

