#ifndef __RAY_TRACER_PLANE_INCLUDED
#define __RAY_TRACER_PLANE_INCLUDED

#include "Vector.h"
#include "Line.h"
#include <utility>
class Plane {
	private:
		const Vector _v;
		const Vector _u;
		const Vector _offset;
	public:
		Plane(const Vector& v, const Vector& u, const Vector& offset);
		Vector u() const;
		Vector v() const;
		Vector offset() const;
};
#endif
