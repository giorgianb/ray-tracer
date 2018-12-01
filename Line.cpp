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

Vector evaluate(const Line& l, const double& s) {
	return s*l.direction() + l.offset();
}

Vector normal(const Line& l, const Vector& v) {
	return normalize(l.direction() % v);
}
