#ifndef __RAY_TRACER_LIGHT_SOURCE_INCLUDED
#define __RAY_TRACER_LIGHT_SOURCE_INCLUDED

#include "Vector.h"
#include <vector>

class LightSource {
	public:
		virtual ~LightSource();

		virtual double brightness() const = 0;
		virtual Vector position() const = 0;
};

using LightSourceList = std::vector<LightSource*>;
#endif
