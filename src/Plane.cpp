#include "Plane.h"
#include "Linear.h"
#include <utility>

#include <cassert>

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


PointPlaneIntersection intersection(const Plane& p, const Vector& tp) {
	AugmentedMatrix am {
		{
			{p.u().x(), p.v().x()},
			{p.u().y(), p.v().y()},
			{p.u().z(), p.v().z()}
		},
		{
			{tp.x() - p.offset().x()},
			{tp.y() - p.offset().y()},
			{tp.z() - p.offset().z()}
		}
	};

	const SolutionSet s {solution(rref_in_place(am))};
	switch (s.first) {
		case SolutionSetType::unique:
			return {PointPlaneIntersectionType::point, tp};
		case SolutionSetType::infinite:
			assert(false);
			return {PointPlaneIntersectionType::none, {0, 0, 0}};
		case SolutionSetType::none:
			return {PointPlaneIntersectionType::none, {0, 0, 0}};
	}
}

LinePlaneIntersection intersection(const Plane& p, const Line& l) {
	AugmentedMatrix am {
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

	const SolutionSet s {solution(rref_in_place(am))};
	switch (s.first) {
		case SolutionSetType::unique:
			return {LinePlaneIntersectionType::point, evaluate(l, s.second[0][0])};
		case SolutionSetType::infinite:
			return {LinePlaneIntersectionType::line, {0, 0, 0}};
		case SolutionSetType::none:
			return {LinePlaneIntersectionType::none, {0, 0, 0}};
	}
}
