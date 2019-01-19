#ifndef __RAY_TRACER_LINE_UTILS_INCLUDED
#define __RAY_TRACER_LINE_UTILS_INCLUDED
#include "Line.h"
#include "Intersection.h"

Vector evaluate(const Line& l, const double& s);
Vector normal(const Line& l, const Vector& v);
Intersection intersection(const Line& l1, const Line& l2);
Intersection intersection(const Line& l, const Vector& v);

#endif
