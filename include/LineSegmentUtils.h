#ifndef __RAY_TRACER_LINE_SEGMENT_UTILS_INCLUDED
#define __RAY_TRACER_LINE_SEGMENT_UTILS_INCLUDED
#include "LineSegment.h"
#include "Intersection.h"

MaybeVector evaluate(const LineSegment& ls, const double& s);
Vector normal(const LineSegment& ls, const Vector& v);
Intersection intersection(const LineSegment& ls, const Line& l);
Intersection intersection(const LineSegment& ls, const Vector& v);

#endif
