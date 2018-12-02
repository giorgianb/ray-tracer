#ifndef __RAY_TRACER_DEBUG_INCLUDED
#define __RAY_TRACER_DEBUG_INCLUDED
#include "Vector.h"
#include "Line.h"
#include "Plane.h"
#include "Linear.h"
#include <iostream>
void print_vector(std::ostream& os, const Vector& v);
void print_line(std::ostream& os, const Line& l);
void print_plane(std::ostream& os, const Plane& p);
void print_matrix(std::ostream& os, const Matrix& m);
#endif
