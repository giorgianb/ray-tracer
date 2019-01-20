#ifndef __RAY_TRACER_POINT_LIGHT_SOURCE_INCLUDED
#define __RAY_TRACER_POINT_LIGHT_SOURCE_INCLUDED

#include "LightSource.h"

class PointLightSource: public LightSource {
	private:
		const Vector _position;
		const double _brightness;
	public:
		PointLightSource(const Vector& position, const double brightness);
		double brightness() const;
		Vector position() const;
};

using LightSourceList = std::vector<LightSource*>;
#endif
