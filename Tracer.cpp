#include "Tracer.h"
#include "Vector.h"
#include "Line.h"

#include "Sphere.h"

#include <limits>
#include <cmath>
#include <iostream>

void print_vector(const Vector& v) {
	std::cout << "Vector {" << v.x() << ", " << v.y() << ", " << v.z() << "}";
}

void print_line(const Line& l) {
	std::cout << "Line {";
	print_vector(l.direction());
	std::cout << ", ";
	print_vector(l.offset());
	std::cout << "}";
}

void print_sphere(const Sphere& s) {
	std::cout << "Sphere {";
	print_vector(s.pos());
	std::cout << ", " << s.radius() << "}";
}

image trace(const SurfaceList& world, 
		const Vector& eye,
		const ResSpec& resolution, 
		const Corner& c1, 
		const Corner& c2) {
	const int xmin {std::min(c1.first, c2.first)};
	const int xmax {std::max(c1.first, c2.first)};
	const int ymin {std::min(c1.second, c2.second)};
	const int ymax {std::max(c1.second, c2.second)};

	const double xscale {((double) (xmax - xmin))/resolution.first};
	const double yscale {((double) (ymax - ymin))/resolution.second};

	// automatically filled with zeroes
	image traced;
	for (size_t i {0}; i < resolution.first; ++i)
		traced.push_back(std::vector<unsigned char>(resolution.second));

	for (size_t i {0}; i < resolution.first; ++i) {
		const double x {xmin + i*xscale};
		for (size_t j {0}; j < resolution.second; ++j) {
			const double y {ymin + j*yscale};

			// Ray from our eye to our current (x, y)
			const Line ray {{Vector {x, y, 0} - eye}, eye};

			// Find closest hit
			double distance {std::numeric_limits<double>::infinity()};
			Surface* hit {nullptr};
			for (const auto& surface: world) {
				MaybeVector phit {surface->intersection(ray)};
				if (phit.first && magnitude(phit.second - eye) < distance) {
					hit = surface;
					distance = magnitude(phit.second - eye);
				}
			}

			// We have a hit, find its color
			if (hit) {
				const Vector h {hit->intersection(ray).second};
				const Color sc {hit->color(h)};
				const Vector dir {ray.direction()};
				double intensity {std::abs(normalize(dir)*hit->normal(h, eye)) * sc};
				traced[i][j] = std::max(0.0, std::round(intensity * 255));
			}
		}
	}

	return traced;
}
