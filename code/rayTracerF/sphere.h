#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "texturedLambertian.h"

class sphere : public hittable {
public:
	sphere() {}
	~sphere() {
		delete mat_ptr;
		if (tex != NULL) {
			//delete tex;
		}
	}
	sphere(vec3 cen, float r, material* m, constant_texture* t = NULL)
		: center(cen), radius(r), mat_ptr(m), tex(t) {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3 center;
	float radius;
	material *mat_ptr;
	constant_texture* tex;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr; 
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr; 
			return true;
		}
	}
	return false;
}
#endif