#ifndef __RAY_TRACER_POLYGON_UTILS_INCLUDED
#define __RAY_TRACER_POLYGON_UTILS_INCLUDED
#include "Polygon.h"
#include "Intersection.h"

Vector normal(const Polygon& p);
Intersection intersection(const Polygon& p, const Vector& tp);
Intersection intersection(const Polygon& p, const Line& l);
#endif
