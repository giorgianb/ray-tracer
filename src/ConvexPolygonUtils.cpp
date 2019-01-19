#include "ConvexPolygonUtils.h"
#include "LineUtils.h"
#include "PlaneUtils.h"
#include "Linear.h"
#include <algorithm>
#include <cmath>

#include <cassert>

std::vector<Vector> convex_hull(std::vector<Vector> polygon);

Vector normal(const ConvexPolygon& p) {
	return normal(p.plane());
}

bool contains(const ConvexPolygon& p, const Vector& tp) {
	std::vector<Vector> points {tp};
	// find intersection of line with slope of edge perpendicular and offset of tp with edge
	for (const auto& edge: p.edges()) {
		if (!std::holds_alternative<EmptySet>(intersection(edge, tp)))
			return false;

		const Line perp {normal(edge, normal(p.plane())), tp};
		const Intersection pi {intersection(edge, perp)}; // polygon intersection
		if (const auto solp = std::get_if<Vector>(&pi))
			points.push_back(*solp);
		else
			return false;
	}

	// Convert points to plane coordinates
	std::vector<Vector> plane_points;
	for (const auto& point: points) {
		AugmentedMatrix am {
			{
				{p.plane().u().x(), p.plane().v().x()},
				{p.plane().u().y(), p.plane().v().y()},
				{p.plane().u().z(), p.plane().v().z()}
			},
			{
				{-p.plane().offset().x() + point.x()},
				{-p.plane().offset().y() + point.y()},
				{-p.plane().offset().z() + point.z()}
			}
		};

		const SolutionSet s {solution(rref_in_place(am))};
		assert(s.first == SolutionSetType::unique);
		assert(std::fabs(s.second[2][0]) <= ESP);
		plane_points.push_back({s.second[0][0], s.second[1][0], 0});
	}

	const Vector tpp {plane_points[0]}; // get tp's coordinate in the plane

	// remove duplicate points
	std::sort(plane_points.begin(), plane_points.end());
	auto last = std::unique(plane_points.begin(), plane_points.end());
	plane_points.erase(last, plane_points.end());

	const std::vector<Vector> ch {convex_hull(plane_points)};
	for (size_t i {0}; i < ch.size() - 1; ++i) {
		const Line edge {ch[i + 1] - ch[i], ch[i]};
		if (!std::holds_alternative<EmptySet>(intersection(edge, tpp)))
			return false;
	}

	return std::find(ch.begin(), ch.end(), tpp) == ch.end();
}

Intersection intersection(const ConvexPolygon& p, const Line& l) {
	const Intersection s {intersection(p.plane(), l)};
	// Test if intersection is in the polygon's plane
	if (std::holds_alternative<EmptySet>(s) || std::holds_alternative<Line>(s))
		return s;
	else if (const auto solp = std::get_if<Vector>(&s)) {
		// get intersection point 
		const Vector ip {*solp};

		return contains(p, ip) ? Intersection {ip} : Intersection {EmptySet {}};
	} else
		return EmptySet {};
}


std::vector<Vector> convex_hull(std::vector<Vector> P) {
	const size_t n {P.size()};

	Vector pivot {0, 0, 0};
	const auto anglecmp = [&pivot](const Vector& a, const Vector& b) {
		const Vector d1 {a - pivot};
		const Vector d2 {b - pivot};
		if (magnitude(d1 % d2) == 0) // are they collinear ?
			return magnitude(d1) < magnitude(d2); // return closest

		return std::atan2(d1.y(), d1.x()) < std::atan2(d2.y(), d2.x());
	};

	if (n <= 3) {
		if (n == 1)
			P.push_back(P[0]);
		else if (P.front() != P.back()) {
			pivot = P[0];
			sort(P.begin() + 1, P.end(), anglecmp);
			P.push_back(P[0]);
		} else {
			P.pop_back();
			pivot = P[0];
			sort(P.begin() + 1, P.end(), anglecmp);
		}

		return P;
	}

	size_t P0 {0};
	for (size_t i {1}; i < n; ++i)
		if (P[i].y() < P[P0].y() || (P[i].y() == P[P0].y() && P[i].x() > P[P0].x()))
			P0 = i;

	std::swap(P[P0], P[0]);
	pivot = P[0];
	sort(P.begin() + 1, P.end(), anglecmp);

	std::vector<Vector> S {P[n - 1], P[0], P[1]};

	size_t i {2};
	while (i < n) {
		size_t j {S.size() - 1};
		assert(S.size() > 1);
		// test if ccw(S[j - 1], S[j], P[i]
		// (q - p) x (r - p) > 0
		if (((S[j] - S[j-1]) % (P[i] - S[j-1])).z() > 0)
			S.push_back(P[i++]);
		else
			S.pop_back();
	}

	return S;
}