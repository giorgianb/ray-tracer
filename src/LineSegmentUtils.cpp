#include "LineSegmentUtils.h"
#include "LineUtils.h"
#include "RayUtils.h"

MaybeVector evaluate(const LineSegment& ls, const double& s) {
	const Vector v {evaluate(ls.line(), s)};

	if (v >= ls.begin() && v <= ls.end())
		return v;

	return {};
}

Vector normal(const LineSegment& ls, const Vector& v) {
	return normal(ls.line(), v);
}

Intersection intersection(const LineSegment& ls, const Line& l) {
	const Intersection inter {intersection(ls.line(), l)};

	if (const auto solp = std::get_if<Vector>(&inter))
		return (*solp >= ls.begin() && *solp <= ls.end()) ? 
			Intersection {*solp} : Intersection {EmptySet {}};
	else if (std::holds_alternative<Line>(inter))
		return ls;
	else
		return EmptySet {};
}

Intersection intersection(const LineSegment& ls, const Vector& v) {
	const Intersection inter {intersection(ls.line(), v)};

	if (const auto solp = std::get_if<Vector>(&inter))
		return (*solp >= ls.begin() && *solp <= ls.end()) ? 
			Intersection {*solp} : Intersection {EmptySet {}};
	else
		return EmptySet {};
}

Intersection intersection(const LineSegment& ls, const Ray& r) {
	const Intersection inter {intersection(r, ls.line())};

	if (const auto sol = std::get_if<Vector>(&inter))
		return (*sol >= ls.begin() && *sol <= ls.end()) ?
			Intersection {*sol} : Intersection {EmptySet {}};
	else if (const auto sol = std::get_if<Ray>(&inter)) {
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
