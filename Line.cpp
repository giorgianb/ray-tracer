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

//#include "debug.h"
LineLineIntersection intersection(const Line& l1, const Line& l2) {
	const AugmentedMatrix am {
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

//	std::cout << "intersection: " << l1 << " and " << l2 << ": ";
	const SolutionSet s {solution(rref(am))};
	switch (s.first) {
		case SolutionSetType::unique:
			assert(std::fabs(s.second[2][0]) <= ESP);
//			std::cout << evaluate(l1, s.second[0][0]) << '\n';
			return LineLineIntersection {LineLineIntersectionType::point, 
				evaluate(l1, s.second[0][0])};
		case SolutionSetType::infinite:
//			std::cout << "infinite\n";
			return LineLineIntersection {LineLineIntersectionType::line, {0, 0, 0}};
		case SolutionSetType::none:
//			std::cout << "none\n";
			return LineLineIntersection {LineLineIntersectionType::none, {0, 0, 0}};
	}
}


LineVectorIntersection intersection(const Line& l, const Vector& v) {
	const AugmentedMatrix am {
		{
			{l1.direction().x()},
			{l1.direction().y()},
			{l1.direction().z()},
		},
		{
			{-l1.offset().x() + v.x()},
			{-l1.offset().y() + v.y()},
			{-l1.offset().z() + v.z()},
		}
	};

//	std::cout << "intersection: " << l1 << " and " << l2 << ": ";
	const SolutionSet s {solution(rref(am))};
	switch (s.first) {
		case SolutionSetType::unique:
			assert(std::fabs(s.second[2][0]) <= ESP);
			return LineVectorIntersection {LineVectorIntersectionType::point, v};
		case SolutionSetType::infinite:
			return LineVectorIntersection {LineVectorIntersectionType::line, {0, 0, 0}};
		case SolutionSetType::none:
			return LineVectorIntersection {LineVectorIntersectionType::none, {0, 0, 0}};
	}
}
