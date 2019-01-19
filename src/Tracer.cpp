#include "Tracer.h" 
#include "Vector.h" 
#include "Line.h"

#include <limits>
#include <cmath>
#include <iostream>

PPMImage trace(const SurfaceList& world, 
		const Vector& eye,
		const ResSpec& resolution, 
		const Corner& c1, 
		const Corner& c2,
		const double plane_offset,
		const double brightness) {
	const int xmin {std::min(c1.first, c2.first)};
	const int xmax {std::max(c1.first, c2.first)};
	const int ymin {std::min(c1.second, c2.second)};
	const int ymax {std::max(c1.second, c2.second)};

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
			const Line ray {to_plane, eye};

			// Find closest hit
			double distance {std::numeric_limits<double>::infinity()};
			Surface* s {nullptr};
			MaybeVector hit {};
			for (const auto& surface: world) {
				const MaybeVector phit {surface->intersection(ray)};
				// also assures us that it is in front of the eye
				if (phit && magnitude(*phit - eye) < distance
						&& (*phit - eye) * to_plane > 0) {
					s = surface;
					hit = *phit;
					distance = magnitude(*phit - eye);
				}
			}

			// We have a hit, find its color
			if (hit) {
				const Color sc {s->color(*hit)};
				const Vector dir {ray.direction()};
				double ri {std::abs(normalize(dir)*s->normal(*hit, eye)) * sc.r};
				double bi {std::abs(normalize(dir)*s->normal(*hit, eye)) * sc.b};
				double gi {std::abs(normalize(dir)*s->normal(*hit, eye)) * sc.g};
				ri /= (magnitude(*hit - eye) * magnitude(*hit - eye));
				ri = std::min(255.0, std::round(ri * brightness * 255));
				bi /= (magnitude(*hit - eye) * magnitude(*hit - eye));
				bi = std::min(255.0, std::round(bi * brightness * 255));
				gi /= (magnitude(*hit - eye) * magnitude(*hit - eye));
				gi = std::min(255.0, std::round(gi * brightness * 255));

				traced[i][j] = {
					static_cast<unsigned char>(ri),
					static_cast<unsigned char>(bi),
					static_cast<unsigned char>(gi)
				};
			}
		}
	}

	return traced;
}
