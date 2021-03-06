#ifndef __RAY_TRACER_DEBUG_INCLUDED
#define __RAY_TRACER_DEBUG_INCLUDED
#include "Vector.h"
#include "Line.h"
#include "LineSegment.h"
#include "Ray.h"
#include "Plane.h"
#include "Linear.h"
#include <iostream>
std::ostream& operator<<(std::ostream& os, const Vector& v);
std::ostream& operator<<(std::ostream& os, const Line& l);
std::ostream& operator<<(std::ostream& os, const LineSegment& ls);
std::ostream& operator<<(std::ostream& os, const Ray& r);
std::ostream& operator<<(std::ostream& os, const Plane& p);
std::ostream& operator<<(std::ostream& os, const Matrix& m);
#endif
