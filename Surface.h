#ifndef __RAY_TRACER_SURFACE_INCLUDED
#define __RAY_TRACER_SURFACE_INCLUDED

#include "Line.h"
#include <utility>

class Surface {
	public:
		virtual MaybeVector intersection(const Line& ray) const;
		virtual Vector normal(const Vector& point, const Vector& light) const;
};
#endif
