#ifndef __RAY_TRACER_SURFACE_CONVEX_POLYGON_INCLUDED
#define __RAY_TRACER_SURFACE_CONVEX_POLYGON_INCLUDED

#include "ConvexPolygon.h"
#include "Surface.h"
#include "Vector.h"

class SurfaceConvexPolygon: public Surface {
	private:
		const ConvexPolygon _poly;
		const Color _color;
	public:
		MaybeVector intersection(const Line& ray) const;
		Vector normal(const Vector& point, const Vector& light) const;
		Color color(const Vector& point) const;

		SurfaceConvexPolygon(const ConvexPolygon p, const Color c);
		ConvexPolygon convex_polygon() const;
};
#endif
