#ifndef __RAY_TRACER_MATERIAL_INCLUDED
#define __RAY_TRACER_MATERIAL_INCLUDED

#include <vector>

struct Color {
	double r, g, b;
};

struct Material {
	const double reflectivity;
	const double refractivity;
	const double transparency;
	const double diffusivity;
	const Color color;
};


using MaterialList = std::vector<Material>;

#endif
