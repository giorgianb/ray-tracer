#include "Sphere.h"
#include "RayUtils.h"
#include <cassert>
#include <cmath>

Sphere::Sphere(const Vector pos, const double radius, const Color color): 
	_pos {pos}, _radius {radius}, _color {color} {
}

Vector Sphere::pos() const {
	return _pos;
}

double Sphere::radius() const {
	return _radius;
}

MaybeVector Sphere::intersection(const Ray& ray) const {
	const double dx {ray.direction().x()};
	const double dy {ray.direction().y()};
	const double dz {ray.direction().z()};

	const double cx {ray.offset().x() - pos().x()};
	const double cy {ray.offset().y() - pos().y()};
	const double cz {ray.offset().z() - pos().z()};

	const double a {dx*dx + dy*dy + dz*dz};
	const double b {2*(cx*dx + cy*dy + cz*dz)};
	const double c {cx*cx + cy*cy + cz*cz - _radius*_radius};

	const double d {b*b - 4*a*c};
	// Solution doesn't exist
	if (d < 0) 
		return {};

	// Otherwise, use minimum root
	const double s {(-b - std::sqrt(d))/(2*a)};

	return evaluate(ray, s);
}

Vector Sphere::normal(const Vector& point, const Vector& light) const {
	assert(std::fabs(magnitude(point - _pos) - _radius) < 0.001);

	return normalize(point - _pos);
}

Color Sphere::color(const Vector& point) const {
	assert(std::fabs(magnitude(point - _pos) - _radius) < 0.001);

	return _color;
}
