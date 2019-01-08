#include "LineSegmentUtils.h"

MaybeVector evaluate(const LineSegment& ls, const double& s) {
	const Vector v {evaluate(ls.line(), s)};

	if (v >= ls.begin() && v <= ls.end())
		return {true, v};

	return {false, {0, 0, 0}};
}

Vector normal(const LineSegment& ls, const Vector& v) {
	return normal(ls.line(), v);
}

Intersection intersection(const LineSegment& ls, const Line& l) {
	auto [type, sol] = intersection(ls.line(), l);

	switch (type) {
		case LineLineIntersectionType::none:
			return EmptySet {};
		case LineLineIntersectionType::point:
			return (sol >= ls.begin() && sol <= ls.end()) ? 
				Intersection {sol} : Intersection {EmptySet {}};
		case LineLineIntersectionType::line:
			return ls;
	}
}

Intersection intersection(const LineSegment& ls, const Vector& v) {
	auto [type, sol] = intersection(ls.line(), v);

	switch (type) {
		case LineVectorIntersectionType::none:
			return EmptySet {};
		case LineVectorIntersectionType::point:
			return (sol >= ls.begin() && sol <= ls.end()) ? 
				Intersection {sol} : Intersection {EmptySet {}};
	}
}
