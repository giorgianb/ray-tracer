#ifndef __RAY_TRACER_RAY_INCLUDED
#define __RAY_TRACER_RAY_INCLUDED

#include "Vector.h"
#include "Line.h"

class Ray {
	private:
		const Line line;
	public:
		constexpr Ray(const Vector& direction, const Vector& offset) noexcept;
		constexpr Vector direction() const noexcept;
		constexpr Vector offset() const noexcept;
};

constexpr Ray::Ray(const Vector& dir, const Vector& off) noexcept: line {dir, off} {
}

constexpr Vector Ray::direction() const noexcept {
	return line.direction();
}

constexpr Vector Ray::offset() const noexcept {
	return line.offset();
}
#endif
