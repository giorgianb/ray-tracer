#include "LineUtils.h"
#include "Linear.h"
#include <cmath>

#include <cassert>

Vector evaluate(const Line& l, const double& s) {
	return s*l.direction() + l.offset();
}

Vector normal(const Line& l, const Vector& v) {
	return normalize(l.direction() % v);
}

Intersection intersection(const Line& l1, const Line& l2) {
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

	const SolutionSet s {solution(rref_in_place(am))};
	switch (s.first) {
		case SolutionSetType::none:
			return EmptySet {};
		case SolutionSetType::unique:
			assert(std::fabs(s.second[2][0]) <= ESP);
			return evaluate(l1, s.second[0][0]);
		case SolutionSetType::infinite:
			return l1;
	}
}

Intersection intersection(const Line& l, const Vector& v) {
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

	const SolutionSet s {solution(rref_in_place(am))};
	switch (s.first) {
		case SolutionSetType::none:
			return EmptySet {};
		case SolutionSetType::unique:
			assert(std::fabs(s.second[2][0]) <= ESP);
			return v;
		case SolutionSetType::infinite:
			assert(false);
			return EmptySet {};
	}
}
