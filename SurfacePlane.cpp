#include "SurfacePlane.h"
#include "Linear.h"

#include <cassert>

#include <iostream>
void print_matrix(std::ostream& os, const Matrix& m) {
	for (size_t i {0}; i < m.size(); ++i) {
		for (size_t j {0}; j < m[i].size(); ++j)
			os << m[i][j] << " ";
		os << '\n';
	}
}

SurfacePlane::SurfacePlane(const Plane p, const Color c): _plane {p}, _color {c} {
}

Plane SurfacePlane::plane() const {
	return _plane;
}

MaybeVector SurfacePlane::intersection(const Line& ray) const {
	AugmentedMatrix am {create_matrix(3, 3), create_matrix(3, 1)};
	am.first[0][0] = ray.direction().x();
	am.first[1][0] = ray.direction().y();
	am.first[2][0] = ray.direction().z();
	am.first[0][1] = -_plane.u().x();
	am.first[1][1] = -_plane.u().y();
	am.first[2][1] = -_plane.u().z();
	am.first[0][2] = -_plane.v().x();
	am.first[1][2] = -_plane.v().y();
	am.first[2][2] = -_plane.v().z();
	am.second[0][0] = _plane.offset().x() - ray.offset().x();
	am.second[1][0] = _plane.offset().y() - ray.offset().y();
	am.second[2][0] = _plane.offset().z() - ray.offset().z();

	am = rref(am);
	if (number_solutions(am) == unique)
		return {true, evaluate(ray, solution(am).second[0][0])};
	else
		return {false, {0, 0, 0}};
}

Vector SurfacePlane::normal(const Vector& point, const Vector& light) const {
	// TODO: add some insertion to make sure the point is in the plane
	using ::normal;
	const Vector v {light - point};
	const Vector n {normal(_plane)};

	return n*v > 0 ? n : -n;
}

Color SurfacePlane::color(const Vector& point) const {
	// TODO: add some insertion to make sure the point is in the plane
	return _color;
}
