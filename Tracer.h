#ifndef __RAY_TRACER_TRACER_INCLUDED
#define __RAY_TRACER_TRACER_INCLUDED

#include "Surface.h"
#include "Vector.h"
#include <vector>
#include <utility>

using image = std::vector<std::vector<unsigned char>>;

using ResSpec = std::pair<size_t, size_t>;
using Corner = std::pair<int, int>;

image trace(const SurfaceList& world, 
		const Vector& eye,
		const ResSpec& resolution, 
		const Corner& c1, 
		const Corner& c2,
		const double plane_offset);
#endif
