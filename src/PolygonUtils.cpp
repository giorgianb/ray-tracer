#include "PolygonUtils.h"
#include "LineSegmentUtils.h"
#include "ConvexPolygon.h"

#include "Debug.h"

Vector normal(const Polygon& p) {
	return normal(p.plane());
}

Intersection intersection(const Polygon& p, const Vector& tp) {
	// TODO: Test if tp is in the Polygon's plane using intersection(Plane, Vector)
	// Waiting for Plane to acquire such a method
	// Workaround: Testing if line segment from tp to plane offset is in plane
	const Line l {p.plane().u(), tp};
	auto [type, sol] = intersection(p.plane(), l);
	if (type != LinePlaneIntersectionType::line)
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


Intersection intersection_debug(const Polygon& p, const Vector& tp) {
	// TODO: Test if tp is in the Polygon's plane using intersection(Plane, Vector)
	// Waiting for Plane to acquire such a method
	// Workaround: Testing if line segment from tp to plane offset is in plane
	const Line l {p.plane().u(), tp};
	auto [type, sol] = intersection(p.plane(), l);
	if (type != LinePlaneIntersectionType::line)
		return EmptySet {}; // tp not in polygon's plane

	size_t count {0};
	const LineSegmentSet edges {p.edges()};
	const Ray r {p.plane().v(), tp};
	// Count number of times the ray intersects with one of the polygon's edges
	LineSet cp_edges {};	
	for (const auto& edge: edges)
		cp_edges.push_back(edge.line());
	bool should_contain {contains({p.plane(), cp_edges}, tp)};
	

	
	std::cerr << "=================================BEGIN================================\n";
	std::cerr << "vertices ";
	for (const auto& v: p.vertices())
		std::cerr << v << ' ';
	std::cerr << '\n';
	std::cerr << "testing: " << tp << '\n';
	for (const auto& edge: edges) {
		const Intersection inter {intersection(edge, r)};
		if (const auto s = std::get_if<Vector>(&inter))
			count += *s != edge.end();

		if (const auto s = std::get_if<Vector>(&inter))
			std::cerr << "intersection:" << "\n\t" << edge << "\n\t" << r << "\n\t"
				<< *s << '\n';
		else if (const auto s = std::get_if<LineSegment>(&inter))
			std::cerr << "intersection:" << "\n\t" << edge << "\n\t" << r << "\n\t"
				<< *s << '\n';
		else if (std::holds_alternative<EmptySet>(inter))
			std::cerr << "intersection:" << "\n\t" << edge << "\n\t" << r << "\n\t"
				<< "EmptySet" << '\n';
		else 
			std::cerr << "intersection:" << "\n\t" << edge << "\n\t" << r << "\n\t"
				<< "Unknown" << '\n';
      }
	std::cerr << "COUNT: " << count << '\n';
	bool contains {count % 2 != 0};
	if (should_contain != contains)
		std::cerr << "DIFFERENCE " << "should_contain: " << should_contain << '\n';
	std::cerr << "==================================END=================================\n";

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
