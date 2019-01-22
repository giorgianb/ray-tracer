#include "SurfacePolygon.h"
#include "PolygonUtils.h"

SurfacePolygon::SurfacePolygon(const Polygon p, const Material m): 
	_poly {p}, _material {m} {
}

MaybeVector SurfacePolygon::intersection(const Ray& ray) const {
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

MaybeVector SurfacePolygon::transmit(const Ray& ray) const {
	return ray.offset();
}

Material SurfacePolygon::material(const Vector& point) const {
	return _material;
}
