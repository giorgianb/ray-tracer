#ifndef __RAY_TRACER_SURFACE_POLYGON_INCLUDED
#define __RAY_TRACER_SURFACE_POLYGON_INCLUDED

#include "Polygon.h"
#include "Surface.h"
#include "Vector.h"

class SurfacePolygon: public Surface {
	private:
		const Polygon _poly;
		const Material _material;
	public:
		MaybeVector intersection(const Ray& ray) const;
		Vector normal(const Vector& point, const Vector& light) const;
		MaybeVector transmit(const Ray& ray) const;
		Material material(const Vector& point) const;

		SurfacePolygon(const Polygon p, const Material m);
		Polygon polygon() const;
};
#endif
