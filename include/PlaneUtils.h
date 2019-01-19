#ifndef __RAY_TRACER_PLANE_UTILS_INCLUDED
#define __RAY_TRACER_PLANE_UTILS_INCLUDED
#include "Plane.h"
#include "Intersection.h"

Vector evaluate(const Plane& p, const double& s, const double& t);
Vector normal(const Plane& p);
Intersection intersection(const Plane& p, const Vector& tp);
Intersection intersection(const Plane& p, const Line& l);

#endif

