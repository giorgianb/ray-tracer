#ifndef __RAY_TRACER_PLANE_INCLUDED
#define __RAY_TRACER_PLANE_INCLUDED

#include "Vector.h"

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

Vector evaluate(const Plane& p, const double& s, const double& t);
Vector normal(const Plane& p);
#endif
