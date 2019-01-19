#include "Plane.h"

Plane::Plane(const Vector& u, const Vector& v, const Vector& offset):
	_u {u},
	_v {v},
	_offset {offset} {
}

Vector Plane::u() const {
	return _u;
}

Vector Plane::v() const {
	return _v;
}

Vector Plane::offset() const {
	return _offset;
}
