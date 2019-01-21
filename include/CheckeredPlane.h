#ifndef __RAY_TRACER_CHECKERED_PLANE_INCLUDED
#define __RAY_TRACER_CHECKERED_PLANE_INCLUDED

#include "Plane.h"
#include "Surface.h"
#include "Vector.h"

class CheckeredPlane: public Surface {
	private:
		const Plane _plane;
		const ColorList _colors;
	public:
		MaybeVector intersection(const Ray& r) const;
		Vector normal(const Vector& point, const Vector& light) const;
		Color color(const Vector& point) const;

		CheckeredPlane(const Plane p, const ColorList& colors);
		Plane plane() const;
};
#endif


