#include "SurfacePlane.h"
#include "Linear.h"

#include <cassert>

SurfacePlane::SurfacePlane(const Plane p, const Color c): _plane {p}, _color {c} {
}

Plane SurfacePlane::plane() const {
	return _plane;
}

MaybeVector SurfacePlane::intersection(const Line& ray) const {
	using ::intersection;

	const LinePlaneIntersection s {intersection(_plane, ray)};
	if (s.first == LinePlaneIntersectionType::point)
		return {true, s.second};
	else
		return {false, {0, 0, 0}};
}

Vector SurfacePlane::normal(const Vector& point, const Vector& light) const {
	// TODO: add some insertion to make sure the point is in the plane
	using ::normal;
	const Vector v {light - point};
	const Vector n {normal(_plane)};

	return n*v > 0 ? n : -n;
}

Color SurfacePlane::color(const Vector& point) const {
	// TODO: add some insertion to make sure the point is in the plane
	return _color;
}
