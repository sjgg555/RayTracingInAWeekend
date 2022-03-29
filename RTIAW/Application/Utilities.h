#pragma once
#include "stdafx.h"

#include <random>
#include <algorithm>
#include <iostream>

namespace Utilities
{
	inline float RandomFloat()
	{
		static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
		static std::mt19937 generator;
		return distribution(generator);
	}

	float RandomFloat(float min, float max)
	{
		return min + (max - min) * RandomFloat();
	}

	float Clamp(float x, float min, float max)
	{
		return std::clamp<float>(x, min, max);
	}

	void WriteColor(std::ostream& out, Color pixel_color, int samples_per_pixel)
	{
		auto scale = 1.0f / samples_per_pixel;
		auto r = glm::sqrt(pixel_color.r * scale);
		auto g = glm::sqrt(pixel_color.g * scale);
		auto b = glm::sqrt(pixel_color.b * scale);

		out << static_cast<int>(256 * Clamp(r, 0.0f, 0.999f)) << ' '
			<< static_cast<int>(256 * Clamp(g, 0.0f, 0.999f)) << ' '
			<< static_cast<int>(256 * Clamp(b, 0.0f, 0.999f)) << '\n';
	}

	void WriteHeader(std::ostream& out, int image_width, int image_height)
	{
		out << "P3\n" << image_width << " " << image_height << "\n255\n";
	}

	vec3 RandomVec3()
	{
		return vec3(RandomFloat(), RandomFloat(), RandomFloat());
	}

	vec3 RandomVec3(float min, float max)
	{
		return vec3(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
	}

	vec3 RandomVec3InSphere()
	{
		while (true) {
			auto p = RandomVec3(-1, 1);
			if (glm::length2(p) >= 1) continue;
			return p;
		}
	}

	vec3 RandomVec3InHemi(const vec3& normal)
	{
		vec3 vecInSphere = RandomVec3InSphere();
		if (glm::dot(vecInSphere, normal) > 0.0f)
			return vecInSphere;
		else
			return -vecInSphere;
	}

	vec3 RandomUnitVec3()
	{
		return glm::normalize(RandomVec3InSphere());
	}
}