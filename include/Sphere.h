#ifndef __RAY_TRACER_SPHERE_INCLUDED
#define __RAY_TRACER_SPHERE_INCLUDED
#include "Surface.h"
class Sphere: public Surface {
	private:
		const Vector _pos;
		const double _radius;
		const Color _color;
	public:
		MaybeVector intersection(const Line& ray) const;
		Vector normal(const Vector& point, const Vector& light) const;
		Color color(const Vector& point) const;

		Sphere(const Vector pos, const double radius, const Color color);
		Vector pos() const;
		double radius() const;
};
#endif
