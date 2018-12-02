#include "Tracer.h" 
#include "Vector.h" 
#include "Line.h"

#include <limits>
#include <cmath>

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
		for (size_t j {0}; j < resolution.second; ++j) {
			const double y {ymin + j*yscale};

			// Ray from our eye to our current (x, y)
			const Vector to_plane {Vector {x, y, plane_offset + eye.z()} - eye};
			const Line ray {to_plane, eye};

			// Find closest hit
			double distance {std::numeric_limits<double>::infinity()};
			Surface* hit {nullptr};
			for (const auto& surface: world) {
				MaybeVector phit {surface->intersection(ray)};
				// also assures us that it is in front of the eye
				if (phit.first && magnitude(phit.second - eye) < distance
						&& (phit.second - eye) * to_plane > 0) {
					hit = surface;
					distance = magnitude(phit.second - eye);
				}
			}

			// We have a hit, find its color
			if (hit) {
				const Vector h {hit->intersection(ray).second};
				const Color sc {hit->color(h)};
				const Vector dir {ray.direction()};
				double ri {std::abs(normalize(dir)*hit->normal(h, eye)) * sc.r};
				double bi {std::abs(normalize(dir)*hit->normal(h, eye)) * sc.b};
				double gi {std::abs(normalize(dir)*hit->normal(h, eye)) * sc.g};
				ri /= (magnitude(h - eye) * magnitude(h - eye));
				ri = std::min(255.0, std::round(ri * brightness * 255));
				bi /= (magnitude(h - eye) * magnitude(h - eye));
				bi = std::min(255.0, std::round(bi * brightness * 255));
				gi /= (magnitude(h - eye) * magnitude(h - eye));
				gi = std::min(255.0, std::round(gi * brightness * 255));

				traced[i][j] = {ri, bi, gi};
			}
		}
	}

	return traced;
}
