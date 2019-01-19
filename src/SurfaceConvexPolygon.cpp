#include "SurfaceConvexPolygon.h"
#include "ConvexPolygonUtils.h"
#include "PlaneUtils.h"

SurfaceConvexPolygon::SurfaceConvexPolygon(const ConvexPolygon p, const Color c): 
	_poly {p}, _color {c} {
}

MaybeVector SurfaceConvexPolygon::intersection(const Line& ray) const {
	using ::intersection;

	const Intersection s {intersection(_poly, ray)};
	if (const auto solp = std::get_if<Vector>(&s))
		return {true, *solp};
	else
		return {false, {0, 0, 0}};
}

Vector SurfaceConvexPolygon::normal(const Vector& point, const Vector& light) const {
	using ::normal;

	const Vector v {light - point};
	const Vector n {normal(_poly.plane())};

	return n*v > 0 ? n : -n;
}

Color SurfaceConvexPolygon::color(const Vector& point) const {
	return _color;
}

