#include "Polygon.h"
#include "Linear.h"
#include <algorithm>
#include <cmath>

#include <cassert>

Polygon::Polygon(const Plane& p, const PointSet& vertices): _plane {p}, _edges {} {
	// TODO: Fix by testing if each individual vertex is in the plane and filter out those
	// that aren't. Waiting for Plane to have an intersection(Plane, Vector) method
	for (size_t i {0}; i < vertices.size() - 1; ++i) {
		const LineSegment edge {vertices[i], vertices[i + 1]};
		auto [type, sol] = intersection(p, edge.line());
		if (type == LinePlaneIntersectionType::line)
			edges.push_back(edge);
	}
}

Plane Polygon::plane() const {
	return _plane;
}

LineSegmentSet Polygon::edges() const {
	return _edges;
}

PointSet Polygon::vertices() const {
	PointSet vertices {};
	for (const auto& e: _edges)
		vertices.push_back(e.begin());

	return vertices;
}
