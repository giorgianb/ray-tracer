#ifndef __RAY_TRACER_CONVEX_POLYGON_UTILS_INCLUDED
#define __RAY_TRACER_CONVEX_POLYGON_UTILS_INCLUDED
#include "ConvexPolygon.h"
#include "Intersection.h"

Vector normal(const ConvexPolygon& p);
bool contains(const ConvexPolygon& p, const Vector& tp);
Intersection intersection(const ConvexPolygon& p, const Line& l);

#endif
