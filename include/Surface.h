#ifndef __RAY_TRACER_SURFACE_INCLUDED
#define __RAY_TRACER_SURFACE_INCLUDED

#include "Material.h"
#include "Vector.h"
#include "Ray.h"

class Surface {
	public:
		virtual ~Surface();

		virtual MaybeVector intersection(const Ray& ray) const = 0;
		virtual Vector normal(const Vector& point, const Vector& light) const = 0;
		// The ray's offset must be the point on the surface through 
		// where we want to transmit
		virtual MaybeVector transmit(const Ray& ray) const = 0;
		virtual Material material(const Vector& point) const = 0;
};

using SurfaceList = std::vector<Surface*>;
#endif
