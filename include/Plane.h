#ifndef __RAY_TRACER_PLANE_INCLUDED
#define __RAY_TRACER_PLANE_INCLUDED

#include "Vector.h"
#include "Line.h"
#include <utility>
class Plane {
	private:
		const Vector _v;
		const Vector _u;
		const Vector _offset;
	public:
		constexpr Plane(const Vector& v, const Vector& u, const Vector& offset) noexcept;
		constexpr Vector u() const noexcept;
		constexpr Vector v() const noexcept;
		constexpr Vector offset() const noexcept;
};

constexpr Plane::Plane(const Vector& u, const Vector& v, const Vector& offset) noexcept:
	_u {u},
	_v {v},
	_offset {offset} {
}

constexpr Vector Plane::u() const noexcept {
	return _u;
}

constexpr Vector Plane::v() const noexcept {
	return _v;
}

constexpr Vector Plane::offset() const noexcept {
	return _offset;
}
#endif
