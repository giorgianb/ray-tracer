#include "PolygonUtils.h"
#include "LineSegmentUtils.h"
#include "PlaneUtils.h"

Vector normal(const Polygon& p) {
	return normal(p.plane());
}

Intersection intersection(const Polygon& p, const Vector& tp) {
	const Intersection inter {intersection(p.plane(), tp)};
	if (!std::holds_alternative<Vector>(inter))
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
	const Intersection inter{intersection(p.plane(), l)};
	if (std::holds_alternative<Line>(inter))
		return l;
	else if (const auto solp = std::get_if<Vector>(&inter))
		return intersection(p, *solp);
	else
		return EmptySet {};
}
