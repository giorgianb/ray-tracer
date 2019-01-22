#ifndef __RAY_TRACER_SPHERE_INCLUDED
#define __RAY_TRACER_SPHERE_INCLUDED
#include "Surface.h"
class Sphere: public Surface {
	private:
		const Vector _pos;
		const double _radius;
		const Material _material;
	public:
		MaybeVector intersection(const Ray& ray) const;
		Vector normal(const Vector& point, const Vector& light) const;
		MaybeVector transmit(const Ray& ray) const;
		Material material(const Vector& point) const;

		Sphere(const Vector pos, const double radius, const Material material);
		Vector pos() const;
		double radius() const;
};
#endif
