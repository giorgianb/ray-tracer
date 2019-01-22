#ifndef __RAY_TRACER_RENDER_INCLUDED
#define __RAY_TRACER_RENDER_INCLUDED

#include "Surface.h"
#include "LightSource.h"
#include "Vector.h"
#include <vector>
#include <utility>

struct PPMColor {
	unsigned char r, g, b;
	constexpr PPMColor() noexcept;
	constexpr PPMColor(const Color& c) noexcept;
};

constexpr PPMColor::PPMColor(const Color& c) noexcept:
	r {static_cast<unsigned char>(std::min(255.0, std::round(c.r * 255)))},
	b {static_cast<unsigned char>(std::min(255.0, std::round(c.b * 255)))},
	g {static_cast<unsigned char>(std::min(255.0, std::round(c.g * 255)))} {
}


constexpr PPMColor::PPMColor() noexcept: r {}, b {}, g {} {
}

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


constexpr double bias {1000*Float::epsilon};

#endif
