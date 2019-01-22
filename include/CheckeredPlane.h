#ifndef __RAY_TRACER_CHECKERED_PLANE_INCLUDED
#define __RAY_TRACER_CHECKERED_PLANE_INCLUDED

#include "Plane.h"
#include "Surface.h"
#include "Vector.h"

class CheckeredPlane: public Surface {
	private:
		const Plane _plane;
		const MaterialList _materials;
	public:
		MaybeVector intersection(const Ray& r) const;
		Vector normal(const Vector& point, const Vector& light) const;
		MaybeVector transmit(const Ray& ray) const;
		Material material(const Vector& point) const;

		CheckeredPlane(const Plane p, const MaterialList& materials);
		Plane plane() const;
};
#endif


