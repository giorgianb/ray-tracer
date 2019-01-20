#include "SurfacePlane.h"
#include "PlaneUtils.h"

#include <cassert>

SurfacePlane::SurfacePlane(const Plane p, const Color c): _plane {p}, _color {c} {
}

Plane SurfacePlane::plane() const {
	return _plane;
}

MaybeVector SurfacePlane::intersection(const Ray& ray) const {
	using ::intersection;

	const Intersection s {intersection(_plane, ray)};
	if (const auto vp = std::get_if<Vector>(&s))
		return *vp;
	else
		return {};
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
