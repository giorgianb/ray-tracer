#include "Line.h"

Line::Line(const Vector& direction, const Vector& offset):
	_direction {direction},
	_offset {offset} {
}

Vector Line::direction() const {
	return _direction;
}

Vector Line::offset() const {
	return _offset;
}
