#pragma once
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
		auto r = pixel_color.r *= scale;
		auto g = pixel_color.g *= scale;
		auto b = pixel_color.b *= scale;

		out << static_cast<int>(256 * Clamp(r, 0.0f, 0.999f)) << ' '
			<< static_cast<int>(256 * Clamp(g, 0.0f, 0.999f)) << ' '
			<< static_cast<int>(256 * Clamp(b, 0.0f, 0.999f)) << '\n';
	}
}