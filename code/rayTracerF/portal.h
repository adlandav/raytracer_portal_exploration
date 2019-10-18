#ifndef PORTAL_H
#define PORTAL_H

#include "material.h"

class portal : public material {
public:
	portal(const vec3& a, float f, const vec3& o, const vec3& t) : albedo(a), otherCen(o), thisCen(t) {
		if (f < 1) fuzz = f; else fuzz = 1;
	}

	virtual bool scatter(const ray& r_in, const hit_record& rec,
		vec3& attenuation, ray& scattered) const {
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
		scattered.A = scattered.A + (otherCen - thisCen);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
	vec3 albedo;
	float fuzz;
	vec3 thisCen;
	vec3 otherCen;
};

#endif
