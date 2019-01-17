#ifndef __RAY_TRACER_POLYGON_INCLUDED
#define __RAY_TRACER_POLYGON_INCLUDED

#include "Plane.h"
#include "Vector.h"
#include "LineSegment.h"
#include <vector>

using PointSet = std::vector<Vector>;
using LineSegmentSet = std::vector<LineSegment>;

class Polygon {
	private:
		const Plane _plane;
		LineSegmentSet _edges;
		PointSet _vertices;
	public:
		Polygon(const Plane& p, const PointSet& vertices);
		Plane plane() const;
		PointSet vertices() const;
		LineSegmentSet edges() const;
};
#endif
