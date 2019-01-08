#include "PolygonUtils.h"
#include "LineSegmentUtils.h"

Vector normal(const Polygon& p) {
	return normal(p.plane());
}

Intersection intersection(const Polygon& p, const Vector& tp) {
	// TODO: Test if tp is in the Polygon's plane using intersection(Plane, Vector)
	// Waiting for Plane to acquire such a method
	// Workaround: Testing if line segment from tp to plane offset is in plane
	const LineSegment ls {tp, p.plane().offset()};
	auto [type, sol] = intersection(p.plane(), ls.line());
	if (type != LinePlaneIntersectionType::line)
		return EmptySet {}; // tp not in polygon's plane

	size_t count {0};
	const LineSegmentSet edges {p.edges()};
	const Ray r {edges[0].begin() - tp, tp};
	// Count number of times the ray intersects with one of the polygon's edges
	for (const auto& edge: edges)
		if (!std::holds_alternative<EmptySet>(intersection(edge, r)))
			++count;

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
