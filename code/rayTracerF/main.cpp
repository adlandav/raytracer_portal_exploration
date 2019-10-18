#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <fstream>
#include <vector>
#include "vec3.h"
#include "ray.h"
#include "float.h"
#include "hitTableList.h"
#include "sphere.h"
#include "camera.h"
#include "random.h"
#include "hitTable.h"
#include "lambertian.h"
#include "metal.h"
#include "dialetric.h"
#include "portal.h"
#include "texture.h"
#include "checkered.h"

using namespace std;
const float MAXFLOAT = numeric_limits<float>::max();

//DEF
vec3 color(const ray&, hittable*, int);
void makeScene();

int main() {
	makeScene();
	_CrtDumpMemoryLeaks();
	return 0;
}

//IMP
vec3 color(const ray& r, hittable *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, MAXFLOAT, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}
void makeScene() {
	int nx = 2000;
	int ny = 1000;
	int ns = 100;
	ofstream file("Atest.ppm", ios::binary);
	file << "P3\n" << nx << " " << ny << "\n255\n";
	sphere* list[7];
	
	list[0] = new sphere(vec3(0.25, 0.5, -1), 0.5, new lambertian(vec3(0.5, 0.0, 0.5)));
	list[1] = new sphere(vec3(-1.2, 0.7, -1), 0.7, new dielectric(1.5));
	list[2] = new sphere(vec3(0.7, 0.5, -2.0), 0.5, new portal(vec3(0.8, 0.8, 0.8), 0.0, vec3(-3.4, 0.5, -1), vec3(0.7, 0.5, -2.0)));
	list[3] = new sphere(vec3(-3.4, 0.5, -1), 0.5, new portal(vec3(0.8, 0.8, 0.8), 0.0, vec3(0.7, 0.5, -2.0), vec3(-3.4, 0.5, -1)));
	//special spheres
	checker_texture* checker = new checker_texture(
		new constant_texture(vec3(0.0, 0.8, 0.8)),
		new constant_texture(vec3(0.9, 0.9, 0.9))
	);
	list[4] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.0, 0.8, 0.8), checker), checker);
	checker_texture* checker2 = new checker_texture(
		new constant_texture(vec3(0.8, 0.8, 0.0)),
		new constant_texture(vec3(0.9, 0.9, 0.9))
	);
	list[5] = new sphere(vec3(0, 0, -1005), 1000, new lambertian(vec3(0.8, 0.8, 0.8), checker2), checker2);
	checker_texture* checker3 = new checker_texture(
		new constant_texture(vec3(0.8, 0.0, 0.0)),
		new constant_texture(vec3(0.9, 0.9, 0.9))
	);
	list[6] = new sphere(vec3(-1005, 0, 0), 1000, new lambertian(vec3(0.8, 0.8, 0.8), checker3), checker3);

	hittable* world = new hittable_list(list, 7);

	vec3 lookfrom(6, 2, 4);
	vec3 lookat(0, 0.5, -1.0);
	float dist_to_focus = 10.0;
	float aperture = 0.0;

	camera cam(lookfrom, lookat, vec3(0, 1, 0), 20,
		float(nx) / float(ny), aperture, dist_to_focus);

	int prog = 0;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + random_double()) / float(nx);
				float v = float(j + random_double()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			file << ir << " " << ig << " " << ib << "\n";
		}
		cout << (100 - (j * 100 / ny)) << "%" << endl;
	}
	
	for (int i = 0; i < 5; i++) {
		//cout << typeid(list[i]).name() << endl; //returns object type
		delete list[i];
	}
	delete world;
	delete checker;
	delete checker2;
	delete checker3;
	cout << "Complete!" << endl;
}