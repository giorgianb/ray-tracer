#ifndef __RAY_TRACER_CONVEX_POLYGON_INCLUDED
#define __RAY_TRACER_CONVEX_POLYGON_INCLUDED

#include "Plane.h"
#include "Line.h"
#include <vector>

enum class LineConvexPolygonIntersectionType {none, point, line};
using LineConvexPolygonIntersection = std::pair<LineConvexPolygonIntersectionType, Vector>;

using LineSet = std::vector<Line>;

class ConvexPolygon {
	private:
		const Plane _plane;
		LineSet _edges;
	public:
		ConvexPolygon(const Plane& p, const LineSet& edges);
		Plane plane() const;
		LineSet edges() const;
};

Vector normal(const ConvexPolygon& p);
bool contains(const ConvexPolygon& p, const Vector& tp);
LineConvexPolygonIntersection intersection(const ConvexPolygon& p, const Line& l);
#endif
