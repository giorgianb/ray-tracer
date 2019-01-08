#ifndef __RAY_TRACER_LINE_SEGMENT_INCLUDED
#define __RAY_TRACER_LINE_SEGMENT_INCLUDED

#include "Vector.h"
#include "Line.h"

class LineSegment {
	private:
		Line _line;
		Vector _begin;
		Vector _end;
	public:
		LineSegment(const Vector& p1, const Vector& p2);
		Line line() const;
		Vector begin() const;
		Vector end() const;
};
#endif
