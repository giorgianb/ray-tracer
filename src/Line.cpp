#include "Line.h"
#include "Linear.h"
#include <cmath>

#include <cassert>

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

LineLineIntersection intersection(const Line& l1, const Line& l2) {
	AugmentedMatrix am {
		{
			{l1.direction().x(), -l2.direction().x()},
			{l1.direction().y(), -l2.direction().y()},
			{l1.direction().z(), -l2.direction().z()},
		},
		{
			{-l1.offset().x() + l2.offset().x()},
			{-l1.offset().y() + l2.offset().y()},
			{-l1.offset().z() + l2.offset().z()},
		}
	};

	const SolutionSet s {solution(rref_in_place(std::move(am)))};
	switch (s.first) {
		case SolutionSetType::unique:
			assert(std::fabs(s.second[2][0]) <= ESP);
			return LineLineIntersection {LineLineIntersectionType::point, 
				evaluate(l1, s.second[0][0])};
		case SolutionSetType::infinite:
			return LineLineIntersection {LineLineIntersectionType::line, {0, 0, 0}};
		case SolutionSetType::none:
			return LineLineIntersection {LineLineIntersectionType::none, {0, 0, 0}};
	}
}

LineVectorIntersection intersection(const Line& l, const Vector& v) {
	AugmentedMatrix am {
		{
			{l.direction().x()},
			{l.direction().y()},
			{l.direction().z()},
		},
		{
			{-l.offset().x() + v.x()},
			{-l.offset().y() + v.y()},
			{-l.offset().z() + v.z()},
		}
	};

	const SolutionSet s {solution(rref_in_place(std::move(am)))};
	switch (s.first) {
		case SolutionSetType::unique:
			assert(std::fabs(s.second[2][0]) <= ESP);
			return LineVectorIntersection {LineVectorIntersectionType::point, v};
		case SolutionSetType::infinite:
			return LineVectorIntersection {LineVectorIntersectionType::point, v};
		case SolutionSetType::none:
			return LineVectorIntersection {LineVectorIntersectionType::none, {0, 0, 0}};
	}
}
