#ifndef __RAY_TRACER_SURFACE_INCLUDED
#define __RAY_TRACER_SURFACE_INCLUDED

#include "Line.h"
#include "Vector.h"
#include <vector>

struct Color {
	double r, g, b;
};

class Surface {
	public:
		virtual ~Surface();

		virtual MaybeVector intersection(const Line& ray) const = 0;
		virtual Vector normal(const Vector& point, const Vector& light) const = 0;
		virtual Color color(const Vector& point) const = 0;
};

using SurfaceList = std::vector<Surface*>;
#endif
