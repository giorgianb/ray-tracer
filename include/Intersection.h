#ifndef __RAY_TRACER_INTERSECTION_INCLUDED
#define __RAY_TRACER_INTERSECTION_INCLUDED

#include <variant>

struct EmptySet {};
#include "Vector.h"
#include "Line.h"
#include "Ray.h"
#include "LineSegment.h"
#include "Plane.h"

using Intersection = std::variant<EmptySet, Vector, Line, Ray, LineSegment, Plane>;
#endif
