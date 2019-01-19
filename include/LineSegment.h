#ifndef __RAY_TRACER_LINE_SEGMENT_INCLUDED
#define __RAY_TRACER_LINE_SEGMENT_INCLUDED

#include "Vector.h"
#include "Line.h"
#include <cmath>

class LineSegment {
	private:
		const Line _line;
		const Vector _begin;
		const Vector _end;
	public:
		constexpr LineSegment(const Vector& p1, const Vector& p2) noexcept;
		constexpr Line line() const noexcept;
		constexpr Vector begin() const noexcept;
		constexpr Vector end() const noexcept;
};

constexpr LineSegment::LineSegment(const Vector& p1, const Vector& p2) noexcept:
	_line {p2 - p1, p1},
	_begin {std::min(p1, p2)},
	_end {std::max(p1, p2)} {
}
	
constexpr Line LineSegment::line() const noexcept {
	return _line;
}

constexpr Vector LineSegment::begin() const noexcept {
	return _begin;
}

constexpr Vector LineSegment::end() const noexcept {
	return _end;
}
#endif
