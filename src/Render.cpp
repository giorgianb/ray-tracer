#include "Render.h" 
#include "Vector.h" 
#include "Line.h"
#include "Float.h"

#include <limits>
#include <cmath>
#include <iostream>
#include <optional>

std::pair<MaybeVector, Surface*> find_closest_hit(const Ray& r, 
		const Vector& point,
		const SurfaceList& sl);
Color trace(const Ray& ray, const LightSourceList& ll, const SurfaceList& sl);
Color illuminate(const Vector& point, const LightSourceList& ll, const SurfaceList& sl);
Ray with_bias(const Ray& ray);
Vector reflect(const Ray& ray, const Vector& normal);
MaybeVector refract(const Ray& ray, const Vector& normal, const double n1, const double n2);
double incident_angle(const Ray& ray, const Vector& normal);
std::optional<double> refracted_angle(const double n1, const double t1, const double n2);
double reflected_portion(const double n1, const double t1, const double n2, const double t2);


PPMImage render(const World& world, 
		const Vector& eye,
		const ResSpec& resolution, 
		const Corner& c1, 
		const Corner& c2,
		const double plane_offset) {
	const int xmin {std::min(c1.first, c2.first)};
	const int xmax {std::max(c1.first, c2.first)};
	const int ymin {std::min(c1.second, c2.second)};
	const int ymax {std::max(c1.second, c2.second)};

	const auto [ll, sl] = world;

	const double xscale {((double) (xmax - xmin))/resolution.first};
	const double yscale {((double) (ymax - ymin))/resolution.second};

	// automatically filled with zeroes
	PPMImage rendered;
	for (size_t i {0}; i < resolution.first; ++i)
		rendered.push_back(std::vector<PPMColor>(resolution.second));

	for (size_t i {0}; i < resolution.first; ++i) {
		const double x {xmin + i*xscale};
		std::cout << "Progress: " << (100.0 * i)/(resolution.first) << "%\n";
		for (size_t j {0}; j < resolution.second; ++j) {
			const double y {ymax - j*yscale};

			// Ray from our eye to our current (x, y)
			const Vector to_plane {Vector {x, y, plane_offset + eye.z()} - eye};
			const Ray ray {to_plane, eye};
			rendered[i][j] = trace(ray, ll, sl);
		}
	}

	return rendered;
}

std::pair<MaybeVector, Surface*> find_closest_hit(const Ray& r, 
		const Vector& point, 
		const SurfaceList& sl) {
	double distance {std::numeric_limits<double>::infinity()};
	Surface* s {nullptr};
	MaybeVector hit {};
	for (const auto& surface: sl) {
		const MaybeVector phit {surface->intersection(r)};
		if (phit && magnitude(*phit - point) < distance) {
			s = surface;
			hit = *phit;
			distance = magnitude(*phit - point);
		}
	}

	return {hit, s};
}

#include "Debug.h"
#include "Sphere.h"

const Sphere* get_sphere(Surface* s) {
	return dynamic_cast<const Sphere*>(s);
}


// TODO: figure out how to add tinting
Color trace(const Ray& ray, const LightSourceList& ll, const SurfaceList& sl) {
	const auto [hit, s] = find_closest_hit(ray, ray.offset(), sl);
	Color color {0, 0, 0};

	if (hit && s) {
		color = illuminate(*hit, ll, sl);
		const Material m {s->material(*hit)};
		const Vector normal {s->normal(*hit, ray.offset())};

		if (m.reflectivity > 0) {
			// reflect, trace, scale by reflectivity and add to color
			const Ray rf {with_bias({reflect(ray, normal), *hit})};
			const Color rc {trace(rf, ll, sl)};

			color.r += rc.r * m.reflectivity;
			color.b += rc.b * m.reflectivity;
			color.g += rc.g * m.reflectivity;
		}
	}
	return color;
}

// TODO: deal with being inside/outside the medium
MaybeVector refract(const Ray& ray, const Vector& normal, const double n1, const double n2) {
	const double t1 {incident_angle(ray, normal)};
	if (const auto t2 = refracted_angle(n1, t1, n2)) {
		const double n {n1/n2};
		const Vector nn {normalize(normal)};
		const Vector dn {normalize(ray.direction())};
		const double c1 {nn*dn};
		const double c2 {std::sqrt(1 - n*n*std::sin(*t2)*std::sin(*t2))};

		return n*dn + nn*(n*c1 - c2);
	} 

	return {};
}

#include <cassert>
Vector reflect(const Ray& ray, const Vector& normal) {
	const Vector I {normalize(ray.direction())};
	const Vector N {normalize(normal)};

	return normalize(I - 2 * (N * I) * N);
}

double incident_angle(const Ray& ray, const Vector& normal) {
	return normalize(normal) * normalize(ray.direction());
}

// returns reflected light
double fresnel(const double n1, const double t1, const double n2, const double t2) {
	const double ct1 {std::cos(t1)};
	const double ct2 {std::cos(t2)};
	const double frp {(n2*ct1 - n1*ct2)/(n2*ct1 + n1*ct2)};
	const double frn {(n1*ct2 - n2*ct1)/(n1*ct2 + n2*ct1)};

	return 1.0/2.0 * (frp*frp + frn*frn);
}

// returns theta_2 from snell's law
std::optional<double> refracted_angle(const double n1, const double t1, const double n2) {
	if (n1/n2 * std::sin(t1) <= 1)
		return std::asin(n1/n2 * sin(t1));

	return {};
}

// bias so that after reflections/refractions we don't hit the same points twice
Ray with_bias(const Ray& ray) {
	return {ray.direction(), ray.offset() + ray.direction() * bias};
}

// handles diffuse reflection
Color illuminate(const Vector& point, const LightSourceList& ll, const SurfaceList& sl) {
	Color color {0, 0, 0};
	for (const auto& light: ll) {
		const Ray ray {point - light->position(), light->position()};

		const auto [hit, s] = find_closest_hit(ray, light->position(), sl);
		if (hit && s && *hit == point) {
			const Vector pos {light->position()};
			const Vector dir {ray.direction()};
			const Material m {s->material(*hit)};
			const Color sc {m.color};
			const double b {light->brightness() * m.diffusivity};
			// lambert's cosine law
			const double c {std::abs(normalize(dir)*s->normal(*hit, pos))};
			const double r {magnitude(*hit - pos)};

			color.r += b * c * sc.r / (r*r);
			color.b += b * c * sc.b / (r*r);
			color.g += b * c * sc.g / (r*r);
		}
	}

	return color;
}
