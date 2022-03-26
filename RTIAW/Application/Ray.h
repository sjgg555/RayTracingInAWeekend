#pragma once
#include "stdafx.h"

class Ray
{
public:
	Ray(const Point3& origin, const vec3& direction)
		: m_origin(origin), m_direction(direction)
	{}

	Point3 origin() const { return m_origin; }
	vec3 direction() const { return m_direction; }

	Point3 at(float t) const
	{
		return m_origin + (m_direction * t);
	}

private:
	Point3 m_origin;
	vec3 m_direction;
};

