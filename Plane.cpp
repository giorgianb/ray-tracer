#include "Plane.h"
#include "Linear.h"

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

Vector evaluate(const Plane& p, const double& s, const double& t) {
	return s*p.u() + t*p.v() + p.offset();
}

Vector normal(const Plane& p) {
	return normalize(p.u() % p.v());
}

LinePlaneIntersection intersection(const Plane& p, const Line& l) {
	const AugmentedMatrix am {
		{
			{l.direction().x(), -p.u().x(), -p.v().x()},
			{l.direction().y(), -p.u().y(), -p.v().y()},
			{l.direction().z(), -p.u().z(), -p.v().z()},
		},
		{
			{p.offset().x() - l.offset().x()},
			{p.offset().y() - l.offset().y()},
			{p.offset().z() - l.offset().z()}
		}
	};

	const MaybeSolution s {solution(rref(am))};
	switch (s.first) {
		case SolutionSetType::unique:
			return {LinePlaneIntersectionType::point, evaluate(l, s.second[0][0])};
		case SolutionSetType::infinite:
			return {LinePlaneIntersectionType::line, {0, 0, 0}};
		case SolutionSetType::none:
			return {LinePlaneIntersectionType::none, {0, 0, 0}};
	}
}
