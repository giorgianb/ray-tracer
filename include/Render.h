#ifndef __RAY_TRACER_RENDER_INCLUDED
#define __RAY_TRACER_RENDER_INCLUDED

#include "Surface.h"
#include "LightSource.h"
#include "Vector.h"
#include <vector>
#include <utility>

struct PPMColor {
	unsigned char r, g, b;
};

using PPMImage = std::vector<std::vector<PPMColor>>;

using World = std::pair<LightSourceList, SurfaceList>;
using ResSpec = std::pair<size_t, size_t>;
using Corner = std::pair<int, int>;

PPMImage render(const World& world, 
		const Vector& eye,
		const ResSpec& resolution, 
		const Corner& c1, 
		const Corner& c2,
		const double plane_offset);


constexpr bias {10*Float::epsilon};

#endif
