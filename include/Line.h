#ifndef __RAY_TRACER_LINE_INCLUDED
#define __RAY_TRACER_LINE_INCLUDED

#include "Vector.h"

class Line {
	private:
		const Vector _direction;
		const Vector _offset;
	public:
		constexpr Line(const Vector& direction, const Vector& offset) noexcept;
		constexpr Vector direction() const noexcept;
		constexpr Vector offset() const noexcept;
};

constexpr Line::Line(const Vector& direction, const Vector& offset) noexcept:
	_direction {direction},
	_offset {offset} {
}

constexpr Vector Line::direction() const noexcept {
	return _direction;
}

constexpr Vector Line::offset() const noexcept {
	return _offset;
}
#endif
