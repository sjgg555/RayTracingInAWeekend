#pragma once
#include "stdafx.h"
#include "Utilities.h"
#include "Ray.h"
#include "Hittable.h"
#include <glm/gtc/epsilon.hpp>

class Material {
public:
    virtual bool scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scatteredRay) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const Color& a) : m_albedo(a) {}

    virtual bool scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override
    {
        auto scatterDirection = record.normal + Utilities::RandomUnitVec3();

        if (glm::all(glm::epsilonEqual(scatterDirection, vec3{}, vec3{FLT_EPSILON, FLT_EPSILON , FLT_EPSILON })))
        {
            scatterDirection = record.normal;
        }

        scatteredRay = Ray(record.p, scatterDirection);
        attenuation = m_albedo;
        return true;
    }

private:
    Color m_albedo;
};