#pragma once
#include "stdafx.h"
#include "Utilities.h"
#include "Ray.h"

class Camera
{
public:
	Camera(float aspect_ratio)
	{
		auto viewport_height = 2.0f;
		auto viewport_width = aspect_ratio * viewport_height;
		auto focal_length = 1.0f;

		m_origin = Point3(0, 0, 0);
		m_horizontal = vec3(viewport_width, 0, 0);
		m_vertical = vec3(0, viewport_height, 0);
		m_lower_left_corner = m_origin - (m_horizontal / 2.0f) - (m_vertical / 2.0f) - vec3(0, 0, focal_length);
	}

	Ray GetRay(float u, float v)
	{
		return Ray(m_origin, m_lower_left_corner + u * m_horizontal + v * m_vertical - m_origin);
	}

private:
	Point3 m_origin;
	Point3 m_lower_left_corner;
	vec3 m_horizontal;
	vec3 m_vertical;
};