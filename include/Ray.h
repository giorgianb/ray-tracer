#ifndef __RAY_TRACER_RAY_INCLUDED
#define __RAY_TRACER_RAY_INCLUDED

#include "Vector.h"
#include "Line.h"

class Ray {
	private:
		Line line;
	public:
		Ray(const Vector& direction, const Vector& offset);
		Vector direction() const;
		Vector offset() const;
};
#endif
