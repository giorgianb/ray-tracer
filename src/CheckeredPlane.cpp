#include "CheckeredPlane.h"
#include "PlaneUtils.h"

#include <cassert>
#include <cmath>

CheckeredPlane::CheckeredPlane(const Plane p, const ColorList& colors):
	_plane {p},
	_colors {colors} {
		assert(colors.size() > 0);
}

Plane CheckeredPlane::plane() const {
	return _plane;
}

MaybeVector CheckeredPlane::intersection(const Ray& ray) const {
	using ::intersection;

	const Intersection s {intersection(_plane, ray)};
	if (const auto vp = std::get_if<Vector>(&s))
		return *vp;
	else
		return {};
}

Vector CheckeredPlane::normal(const Vector& point, const Vector& light) const {
	using ::normal;
	const Vector v {light - point};
	const Vector n {normal(_plane)};

	return n*v > 0 ? n : -n;
}

// Assumes l1 and l2 intersect. 
// Returns 's' in s(l1.direction()) + l1.offset() = t(l2.direction()) + l2.offset()
double get_first_basis(const Line& l1, const Line& l2) {
	const Vector e {l1.direction()};
	const Vector f {l2.direction()};
	const Vector g {l2.offset() - l1.offset()};
	const Vector h {f % g};
	const Vector k {f % e};
	const double hm {magnitude(h)};
	const double km {magnitude(k)};

	const int sign {(h*k) >= 0 ? 1 : -1};

	return (hm/km)*sign;
}

Color CheckeredPlane::color(const Vector& point) const {
	const double s {get_first_basis({_plane.u(), _plane.offset()}, {_plane.v(), point})};
	const double t {get_first_basis({_plane.v(), _plane.offset()}, {_plane.u(), point})};

	return _colors[static_cast<int>(std::round(s) + std::round(t)) % _colors.size()];
}
