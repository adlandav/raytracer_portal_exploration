#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "texture.h"

class lambertian : public material {
public:
	vec3 albedo;
	texture* albedoTex;

	lambertian(const vec3& a, constant_texture* al = NULL) : albedo(a), albedoTex(al) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec,
		vec3& attenuation, ray& scattered) const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);

		if (albedoTex != NULL) {
			attenuation = albedoTex->value(0, 0, rec.p);
		}
		else {
			attenuation = albedo;
		}
		return true;
	}
};

#endif
