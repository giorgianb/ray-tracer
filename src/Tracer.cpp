#include "Tracer.h" 
#include "Vector.h" 
#include "Line.h"

#include <limits>
#include <cmath>
#include <iostream>

std::pair<MaybeVector, Surface*> find_closest_hit(const Ray& r, 
		const Vector& point,
		const SurfaceList& sl);
PPMColor illuminate(const LightSourceList& ll, const SurfaceList& sl, const Vector& point);

PPMImage trace(const World& world, 
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
	PPMImage traced;
	for (size_t i {0}; i < resolution.first; ++i)
		traced.push_back(std::vector<PPMColor>(resolution.second));

	for (size_t i {0}; i < resolution.first; ++i) {
		const double x {xmin + i*xscale};
		std::cout << "Progress: " << (100.0 * i)/(resolution.first) << "%\n";
		for (size_t j {0}; j < resolution.second; ++j) {
			const double y {ymax - j*yscale};

			// Ray from our eye to our current (x, y)
			const Vector to_plane {Vector {x, y, plane_offset + eye.z()} - eye};
			const Ray ray {to_plane, eye};

			auto [hit, s] = find_closest_hit(ray, eye, sl);

			// We have a hit, illuminate where it hit
			if (hit && s)
				traced[i][j] = 	illuminate(ll, sl, *hit);
		}
	}

	return traced;
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

PPMColor illuminate(const LightSourceList& ll, const SurfaceList& sl, const Vector& point) {
	Color color {0, 0, 0};
	for (const auto& light: ll) {
		const Ray ray {point - light->position(), light->position()};

		auto [hit, s] = find_closest_hit(ray, light->position(), sl);
		if (hit && s && *hit == point) {
			const Vector pos {light->position()};
			const Vector dir {ray.direction()};
			const double b {light->brightness()};
			// lambert's cosine law
			const double c {std::abs(normalize(dir)*s->normal(*hit, pos))};
			const Color sc {s->color(*hit)};
			const double r {magnitude(*hit - pos)};

			color.r += b * c * sc.r / (r*r);
			color.b += b * c * sc.b / (r*r);
			color.g += b * c * sc.g / (r*r);
		}
	}

	return { 
		static_cast<unsigned char>(std::min(255.0, std::round(color.r * 255))),
		static_cast<unsigned char>(std::min(255.0, std::round(color.b * 255))),
		static_cast<unsigned char>(std::min(255.0, std::round(color.g * 255)))
	};
}
