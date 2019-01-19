#include "SurfacePolygon.h"
#include "PolygonUtils.h"

SurfacePolygon::SurfacePolygon(const Polygon p, const Color c): 
	_poly {p}, _color {c} {
}

MaybeVector SurfacePolygon::intersection(const Line& ray) const {
	using ::intersection;

	const Intersection inter {intersection(_poly, ray)};
	if (const auto solp = std::get_if<Vector>(&inter))
		return *solp;
	else
		return {};
}

Vector SurfacePolygon::normal(const Vector& point, const Vector& light) const {
	using ::normal;

	const Vector v {light - point};
	const Vector n {normal(_poly)};

	return n*v > 0 ? n : -n;
}

Color SurfacePolygon::color(const Vector& point) const {
	return _color;
}
