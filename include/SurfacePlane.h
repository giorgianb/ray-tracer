#ifndef __RAY_TRACER_SURFACE_PLANE_INCLUDED
#define __RAY_TRACER_SURFACE_PLANE_INCLUDED

#include "Plane.h"
#include "Surface.h"
#include "Vector.h"

class SurfacePlane: public Surface {
	private:
		const Plane _plane;
		const Material _material;
	public:
		MaybeVector intersection(const Ray& ray) const;
		Vector normal(const Vector& point, const Vector& light) const;
		MaybeVector transmit(const Ray& ray) const;
		Material material(const Vector& point) const;

		SurfacePlane(const Plane p, const Material m);
		Plane plane() const;
};
#endif
