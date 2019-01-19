#ifndef __RAY_TRACER_RAY_UTILS_INCLUDED
#define __RAY_TRACER_RAY_UTILS_INCLUDED
#include "Ray.h"
#include "Intersection.h"
#include "LineUtils.h"

constexpr MaybeVector evaluate(const Ray& r, const double& s) noexcept;
constexpr Vector normal(const Ray& r, const Vector& v) noexcept;
constexpr Intersection intersection(const Ray& r, const Line& l) noexcept;
constexpr Intersection intersection(const Ray& r, const Vector& v) noexcept;

constexpr MaybeVector evaluate(const Ray& r, const double& s) noexcept {
	if (s >= 0)
		return evaluate(Line {r.direction(), r.offset()}, s);

	return {};
}

constexpr Vector normal(const Ray& r, const Vector& v) noexcept {
	return normal(Line {r.direction(), r.offset()}, v);
}

constexpr Intersection intersection(const Ray& r, const Line& l) noexcept {
	const Intersection inter {intersection(Line {r.direction(), r.offset()}, l)};

	if (const auto solp = std::get_if<Vector>(&inter))
		return ((*solp - r.offset()) * r.direction()) >= 0 ?
			Intersection {*solp} : Intersection {EmptySet {}};
	else if (std::holds_alternative<Line>(inter))
		return r;
	else
		return EmptySet {};
}

constexpr Intersection intersection(const Ray& r, const Vector& v) noexcept {
	const Intersection inter {intersection(Line {r.direction(), r.offset()}, v)};

	if (const auto solp = std::get_if<Vector>(&inter))
		return ((*solp - r.offset()) * r.direction()) >= 0 ?
			Intersection {*solp} : Intersection {EmptySet {}};
	else
		return EmptySet {};
}

#endif
