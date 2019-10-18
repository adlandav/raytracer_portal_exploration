#ifndef TEXTUREDLAMBERTIAN_H
#define TEXTUREDLAMBERTIAN_H

#include "material.h"
#include "texture.h"

class texturedlambertian : public material {
public:
	texture* albedo;

	texturedlambertian(texture *a) : albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec,
		vec3& attenuation, ray& scattered) const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo->value(0, 0, rec.p);
		return true;
	}
};

#endif
