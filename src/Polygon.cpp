#include "Polygon.h"
#include "PlaneUtils.h"
#include <algorithm>
#include <cmath>

#include <cassert>

Polygon::Polygon(const Plane& p, const PointSet& vertices): _plane {p}, _edges {}, _vertices {} {
	for (const auto& v: vertices)
		if (std::holds_alternative<Vector>(intersection(p, v)))
			_vertices.push_back(v);

	for (size_t i {0}; _vertices.size() > 0 && i < _vertices.size() - 1; ++i)
		_edges.push_back({_vertices[i], _vertices[i + 1]});
}

Plane Polygon::plane() const {
	return _plane;
}

LineSegmentSet Polygon::edges() const {
	return _edges;
}

PointSet Polygon::vertices() const {
	return _vertices;
}
