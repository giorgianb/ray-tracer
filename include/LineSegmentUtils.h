#ifndef __RAY_TRACER_LINE_SEGMENT_UTILS_INCLUDED
#define __RAY_TRACER_LINE_SEGMENT_UTILS_INCLUDED
#include "LineSegment.h"
#include "Intersection.h"
#include "LineUtils.h"
#include "RayUtils.h"

constexpr MaybeVector evaluate(const LineSegment& ls, const double& s) noexcept;
constexpr Vector normal(const LineSegment& ls, const Vector& v) noexcept;
constexpr Intersection intersection(const LineSegment& ls, const Line& l) noexcept;
constexpr Intersection intersection(const LineSegment& ls, const Vector& v) noexcept;
constexpr Intersection intersection(const LineSegment& ls, const Ray& r) noexcept;

constexpr MaybeVector evaluate(const LineSegment& ls, const double& s) noexcept {
	const Vector v {evaluate(ls.line(), s)};

	if (v >= ls.begin() && v <= ls.end())
		return v;

	return {};
}

constexpr Vector normal(const LineSegment& ls, const Vector& v) noexcept {
	return normal(ls.line(), v);
}

constexpr Intersection intersection(const LineSegment& ls, const Line& l) noexcept {
	const Intersection inter {intersection(ls.line(), l)};

	if (const auto solp = std::get_if<Vector>(&inter))
		return (*solp >= ls.begin() && *solp <= ls.end()) ? 
			Intersection {*solp} : Intersection {EmptySet {}};
	else if (std::holds_alternative<Line>(inter))
		return ls;
	else
		return EmptySet {};
}

constexpr Intersection intersection(const LineSegment& ls, const Vector& v) noexcept {
	const Intersection inter {intersection(ls.line(), v)};

	if (const auto solp = std::get_if<Vector>(&inter))
		return (*solp >= ls.begin() && *solp <= ls.end()) ? 
			Intersection {*solp} : Intersection {EmptySet {}};
	else
		return EmptySet {};
}

constexpr Intersection intersection(const LineSegment& ls, const Ray& r) noexcept {
	const Intersection inter {intersection(r, ls.line())};
	auto check_empty = [](const LineSegment& ls) constexpr noexcept {
		return (ls.begin() == ls.end()) ? Intersection {ls.begin()} : Intersection {ls};
	};

	if (const auto sol = std::get_if<Vector>(&inter))
		return (*sol >= ls.begin() && *sol <= ls.end()) ?
			Intersection {*sol} : Intersection {EmptySet {}};
	else if (const auto sol = std::get_if<Ray>(&inter)) {
		const Ray rsol {*sol};

		if (rsol.offset() <= ls.begin()) {
			if ((ls.begin() - rsol.offset()) * rsol.direction() >= 0)
				return check_empty(ls);
			else
				return EmptySet {};
		} else if (rsol.offset() >= ls.end()) {
			if ((ls.end() - rsol.offset()) * rsol.direction() >= 0)
				return check_empty(ls);
			else
				return EmptySet {};
		// Offset->begin same direction as rsol.direction()
		} else if ((ls.begin() - rsol.offset()) * rsol.direction() >= 0)
			return check_empty({ls.begin(), rsol.offset()});
		// Offset->end same direction as rsol.direction()
		else if ((ls.end() - rsol.offset()) * rsol.direction() >= 0)
			return check_empty({rsol.offset(), ls.end()});
		else 
			return EmptySet {};
	} else
		return EmptySet {};
}
#endif
