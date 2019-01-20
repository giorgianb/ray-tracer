#ifndef __RAY_TRACER_PLANE_UTILS_INCLUDED
#define __RAY_TRACER_PLANE_UTILS_INCLUDED
#include "Plane.h"
#include "Intersection.h"
#include "LineUtils.h"
#include "Linear.h"
#include "Ray.h"
#include "RayUtils.h"
#include <utility>

#include <cassert>
#include <cmath>

constexpr Vector evaluate(const Plane& p, const double& s, const double& t) noexcept;
constexpr Vector normal(const Plane& p) noexcept;
constexpr Intersection intersection(const Plane& p, const Vector& tp) noexcept;
constexpr Intersection intersection(const Plane& p, const Line& l) noexcept;
constexpr Intersection intersection(const Plane& p, const Ray& r) noexcept;

constexpr Vector evaluate(const Plane& p, const double& s, const double& t) noexcept {
	return s*p.u() + t*p.v() + p.offset();
}

constexpr Vector normal(const Plane& p) noexcept {
	return normalize(p.u() % p.v());
}


constexpr Intersection intersection(const Plane& p, const Vector& tp) noexcept {
	const Vector dv {tp - p.offset()};
	// See if (offset -> point) and plane's normal are perpendicular
	
	return (std::fabs(dv * normal(p)) <= ESP) ? Intersection {tp} : Intersection {EmptySet {}};
}

constexpr Intersection intersection(const Plane& p, const Line& l) noexcept {
	// Test if line is in the plane
	// See if plane's normal and line's direction are perpendicular, than see
	// whether the line's offset is in the plane. If it is, than the line and the plane
	// fully intersect. Otherwise, they are parallel
	
	// outline:
	// l = s(a_x, a_y, a_z) + (o_x, o_y, o_z)
	// (A, B, C) = normal(p)
	// d = normal(p) * p.offset()
	// Ax + By + Cz = d 
	// A*(s*a_x + o_x) + B*(s*a_y + o_y) + C*(s*a_z + o_z) = d 
	// => s*((A, B, C) * (a_x, a_y, a_z)) = d - (A, B, C) * (o_x, o_y, o_z)
	const Vector n {normal(p)};
	const double d {n*p.offset()};
	const double constant {d - n*l.offset()};
	const double coeff {n * l.direction()};
	if (std::fabs(coeff) <= ESP)
		return (std::fabs(constant) <= 0) ? Intersection {l} : Intersection {EmptySet {}};

	return evaluate(l, constant / coeff);
}

constexpr Intersection intersection(const Plane& p, const Ray& r) noexcept {
	const Vector n {normal(p)};
	const double d {n*p.offset()};
	const double constant {d - n*r.offset()};
	const double coeff {n * r.direction()};
	if (std::fabs(coeff) <= ESP)
		return (std::fabs(constant) <= 0) ? Intersection {r} : Intersection {EmptySet {}};

	const double s {constant / coeff};
	if (const auto point = evaluate(r, s))
		return *point;

	return {};
}

#endif
