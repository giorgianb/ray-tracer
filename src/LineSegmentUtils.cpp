#include "LineSegmentUtils.h"
#include "RayUtils.h"

#include <cassert>
#include "Debug.h"
#include <iostream>

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

Intersection intersection(const LineSegment& ls, const Ray& r) {
	const Intersection inter {intersection(r, ls.line())};

	if (auto sol = std::get_if<Vector>(&inter))
		return (*sol >= ls.begin() && *sol <= ls.end()) ?
			Intersection {*sol} : Intersection {EmptySet {}};
	else if (auto sol = std::get_if<Ray>(&inter)) {
		const Ray rsol {*sol};
		Intersection ret;

		if (rsol.offset() <= ls.begin()) {
			if ((ls.begin() - rsol.offset()) * rsol.direction() >= 0)
				ret = ls;
			else
				ret = EmptySet {};
		} else if (rsol.offset() >= ls.end()) {
			if ((ls.end() - rsol.offset()) * rsol.direction() >= 0)
				ret = ls;
			else
				ret = EmptySet {};
		// Offset->begin same direction as rsol.direction()
		} else if ((ls.begin() - rsol.offset()) * rsol.direction() >= 0)
			ret =  LineSegment {ls.begin(), rsol.offset()};
		// Offset->end same direction as rsol.direction()
		else if ((ls.end() - rsol.offset()) * rsol.direction() >= 0)
			ret = LineSegment {rsol.offset(), ls.end()};

		if (std::holds_alternative<LineSegment>(ret)) {
			const auto s = std::get<LineSegment>(ret);
			if (s.begin() == s.end())
				ret = s.begin();
		}

		return ret;
	} else
		return EmptySet {};
}
