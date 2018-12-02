#ifndef __RAY_TRACER_LINE_INCLUDED
#define __RAY_TRACER_LINE_INCLUDED

#include "Vector.h"

enum class LineLineIntersectionType {none, point, line};
using LineLineIntersection = std::pair<LineLineIntersectionType, Vector>;

class Line {
	private:
		Vector _direction;
		Vector _offset;
	public:
		Line(const Vector& direction, const Vector& offset);
		Vector direction() const;
		Vector offset() const;
};

Vector evaluate(const Line& l, const double& s);
Vector normal(const Line& l, const Vector& v);
LineLineIntersection intersection(const Line& l1, const Line& l2);
#endif
