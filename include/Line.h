#ifndef __RAY_TRACER_LINE_INCLUDED
#define __RAY_TRACER_LINE_INCLUDED

#include "Vector.h"

class Line {
	private:
		Vector _direction;
		Vector _offset;
	public:
		Line(const Vector& direction, const Vector& offset);
		Vector direction() const;
		Vector offset() const;
};
#endif
