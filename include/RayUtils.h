#ifndef __RAY_TRACER_RAY_UTILS_INCLUDED
#define __RAY_TRACER_RAY_UTILS_INCLUDED
#include "Ray.h"
#include "Intersection.h"

MaybeVector evaluate(const Ray& r, const double& s);
Vector normal(const Ray& r, const Vector& v);
Intersection intersection(const Ray& r, const Line& l);
Intersection intersection(const Ray& r, const Vector& v);

#endif
