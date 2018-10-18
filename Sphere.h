#ifndef __RAY_TRACER_SPHERE_INCLUDED
#define __RAY_TRACER_SPHERE_INCLUDED
#include "Surface.h"
class Sphere: public Surface {
	private:
		const Vector _pos;
		const double _radius;
	public:
		Sphere(const Vector pos, const double radius);
		Vector pos() const;
		double radius() const;
};
#endif
