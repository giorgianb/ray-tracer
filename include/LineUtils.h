#ifndef __RAY_TRACER_LINE_UTILS_INCLUDED
#define __RAY_TRACER_LINE_UTILS_INCLUDED
#include "Line.h"
#include "Intersection.h"
#include "Linear.h"
#include "Float.h"

#include <cmath>

constexpr Vector evaluate(const Line& l, const double& s) noexcept;
constexpr Vector normal(const Line& l, const Vector& v) noexcept;
constexpr Intersection intersection(const Line& l1, const Line& l2) noexcept;
constexpr Intersection intersection(const Line& l, const Vector& v) noexcept;


constexpr Vector evaluate(const Line& l, const double& s) noexcept {
	return s*l.direction() + l.offset();
}

constexpr Vector normal(const Line& l, const Vector& v) noexcept {
	return normalize(l.direction() % v);
}

constexpr Intersection intersection(const Line& l1, const Line& l2) noexcept {
	// Test if the lines are really the same
	if (l1.offset() != l2.offset()) {
		const Vector nd {normalize(l1.direction())};
		const Vector ndv {normalize(l2.offset() - l1.offset())};
		if (ndv == nd || ndv == -nd)
			return l1;
	} else {
		// if they have the same offset, we've found an intersection point, but still check
		// whether the entire line intersections
		const Vector nd1 {normalize(l1.direction())};
		const Vector nd2 {normalize(l2.direction())};

		return (nd1 == nd2 || nd1 == -nd2) ? Intersection {l1} : Intersection {l1.offset()};
	}

	const Vector e {l1.direction()};
	const Vector f {l2.direction()};
	const Vector g {l2.offset() - l1.offset()};
	const Vector h {f % g};
	const Vector k {f % e};
	const double hm {magnitude(h)};
	const double km {magnitude(k)};

	if (std::fabs(hm) <= Float::epsilon || std::fabs(km) <= Float::epsilon)
		return EmptySet {};
	
	const int s {(h*k) >= 0 ? 1 : -1};

	return l1.offset() + e*s*(hm/km);
}

constexpr Intersection intersection(const Line& l, const Vector& v) noexcept {
	if (l.offset() != v) {
		const Vector nd1 {normalize(v - l.offset())};
		const Vector nd2 {normalize(l.direction())};

		return (nd1 == nd2 || nd1 == -nd2) ? Intersection {v} : Intersection {EmptySet {}};
	} else
		return v;
}

#endif
