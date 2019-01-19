#include "ConvexPolygon.h"
#include "PlaneUtils.h"

ConvexPolygon::ConvexPolygon(const Plane& p, const LineSet& edges): _plane {p}, _edges {} {
	for (const auto& edge: edges)
		if (std::holds_alternative<Line>(intersection(p, edge)))
			_edges.push_back(edge);
}

Plane ConvexPolygon::plane() const {
	return _plane;
}

LineSet ConvexPolygon::edges() const {
	return _edges;
}
