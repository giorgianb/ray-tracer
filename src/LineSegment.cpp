#include "LineSegment.h"
#include <cmath>

#include <cassert>

LineSegment::LineSegment(const Vector& p1, const Vector& p2):
	_line {p2 - p1, p1},
	_begin {std::min(p1, p2)},
	_end {std::max(p1, p2)} {
}
	
Line LineSegment::line() const {
	return _line;
}

Vector LineSegment::begin() const {
	return _begin;
}

Vector LineSegment::end() const {
	return _end;
}
