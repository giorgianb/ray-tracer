#include "PolygonUtils.h"
#include "LineSegmentUtils.h"

Vector normal(const Polygon& p) {
	return normal(p.plane());
}

Intersection intersection(const Polygon& p, const Vector& tp) {
	auto [type, sol] = intersection(p.plane(), tp);
	if (type != PointPlaneIntersectionType::point)
		return EmptySet {}; // tp not in polygon's plane

	size_t count {0};
	const LineSegmentSet edges {p.edges()};
	const Ray r {p.plane().v(), tp};
	// Count number of times the ray intersects with one of the polygon's edges
	for (const auto& edge: edges) {
		const Intersection inter {intersection(edge, r)};
		if (const auto s = std::get_if<Vector>(&inter))
			count += *s != edge.end();
	}

	return (count % 2 != 0) ? Intersection {tp} : Intersection {EmptySet {}};
}

Intersection intersection(const Polygon& p, const Line& l) {
	auto [type, sol] = intersection(p.plane(), l);
	switch (type) {
		case LinePlaneIntersectionType::line:
			return l;
		case LinePlaneIntersectionType::point:
			return intersection(p, sol);
		default:
			return EmptySet {};
	}
}
