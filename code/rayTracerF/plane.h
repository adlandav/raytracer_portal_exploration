//#ifndef PLANE_H
//#define PLANE_H
//
//#include "hitTable.h"
//
//class Plane : public hittable {
//	Plane() {}
//	Plane(vec3 ll, vec3 n, float w, float h, material *m)
//		: lowleft(ll), normal(n), width(w), height(h), mat_ptr(m) {};
//	vec3 lowleft;
//	material *mat_ptr;
//	vec3 normal;
//	float width;
//	float height;
//
//
//
//	bool hit(const vec3 &n, const vec3 &p0, const vec3 &l0, const vec3 &l, float &t);
//};
//
//bool Plane::hit(const vec3 &n, const vec3 &p0, const vec3 &l0, const vec3 &l, float &t)
//{
//	// assuming vectors are all normalized
//	float denom = dotProduct(n, l);
//	if (denom > 1e-6) {
//		vec3 p0l0 = p0 - l0;
//		t = dotProduct(p0l0, n) / denom;
//		return (t >= 0);
//	}
//
//	return false;
//}
//
//#endif // !PLANE_H
