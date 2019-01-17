#ifndef __RAY_TRACER_PLANE_INCLUDED
#define __RAY_TRACER_PLANE_INCLUDED

#include "Vector.h"
#include "Line.h"
#include <utility>

enum class PointPlaneIntersectionType {none, point};
using PointPlaneIntersection = std::pair<PointPlaneIntersectionType, Vector>;

enum class LinePlaneIntersectionType {none, point, line};
using LinePlaneIntersection = std::pair<LinePlaneIntersectionType, Vector>;

class Plane {
	private:
		const Vector _v;
		const Vector _u;
		const Vector _offset;
	public:
		Plane(const Vector& v, const Vector& u, const Vector& offset);
		Vector u() const;
		Vector v() const;
		Vector offset() const;
};

Vector evaluate(const Plane& p, const double& s, const double& t);
Vector normal(const Plane& p);
PointPlaneIntersection intersection(const Plane& p, const Vector& tp);
LinePlaneIntersection intersection(const Plane& p, const Line& l);
#endif
