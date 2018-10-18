#include "Plane.h"
Plane(const Vector& u, const Vector& v, const Vector& offset):
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

Vector evaluate(const Plane& p, const double& s, const double& t) {
	return s*p.u() + t*p.v() + p.offset();
}

Vector normal(const Plane& p) {
	return normalize(p.u() % p.v());
}
