#include "ConvexPolygon.h"
#include "Linear.h"
#include <algorithm>
#include <cmath>

#include <cassert>

std::vector<Vector> convex_hull(std::vector<Vector> polygon);

ConvexPolygon::ConvexPolygon(const Plane& p, const LineSet& edges): _plane {p}, _edges {} {
	for (const auto& edge: edges)
		if (intersection(p, edge).first == LinePlaneIntersectionType::line)
			_edges.push_back(edge);
}

Plane ConvexPolygon::plane() const {
	return _plane;
}

LineSet ConvexPolygon::edges() const {
	return _edges;
}

Vector normal(const ConvexPolygon& p) {
	return normal(p.plane());
}

bool contains(const ConvexPolygon& p, const Vector& tp) {
	std::vector<Vector> points {tp};
	// find intersection of line with slope of edge perpendicular and offset of tp with edge
	for (const auto& edge: p.edges()) {
		const Line perp {normal(edge, normal(p.plane())), tp};
		const LineLineIntersection pi {intersection(edge, perp)}; // polygon intersection
		assert (pi.first == LineLineIntersectionType::point);
		points.push_back(pi.second);
	}

	// Convert points to plane coordinates
	const Vector tpp {points[0]}; // get tp's coordinate in the plane
	std::vector<Vector> plane_points;
	for (const auto& point: points) {
		const AugmentedMatrix am {
			{
				{p.plane().u().x(), p.plane().v().x()},
				{p.plane().u().y(), p.plane().v().y()},
				{p.plane().u().z(), p.plane().v().z()}
			},
			{
				{p.plane().offset().x() - tp.x()},
				{p.plane().offset().y() - tp.y()},
				{p.plane().offset().z() - tp.z()}
			}
		};
		const SolutionSet s {solution(rref(am))};
		assert(s.first == SolutionSetType::unique);
		assert(std::fabs(s.second[2][0]) <= ESP);
		plane_points.push_back({s.second[0][0], s.second[1][0], 0});
	}
	plane_points.push_back(plane_points.front()); // for the CH algorithm

	const std::vector<Vector> ch {convex_hull(plane_points)};
	return std::find(ch.begin(), ch.end(), tpp) == ch.end();
}

LineConvexPolygonIntersection intersection(const ConvexPolygon& p, const Line& l) {
	const LinePlaneIntersection s {intersection(p.plane(), l)};
	// Test if intersection is in the polygon's plane
	switch (s.first) {
		case LinePlaneIntersectionType::none:
			return {LineConvexPolygonIntersectionType::none, {0, 0, 0}};
		case LinePlaneIntersectionType::line:
			return {LineConvexPolygonIntersectionType::line, {0, 0, 0}};
		default:
			break;
	}

	// get intersection point 
	const Vector ip {s.second};
	if (contains(p, ip))
		return {LineConvexPolygonIntersectionType::point, ip};
	else
		return {LineConvexPolygonIntersectionType::none, {0, 0, 0}};
}


std::vector<Vector> convex_hull(std::vector<Vector> P) {
	const size_t n {P.size()};
	if (n <= 3) {
		if (P[0] != P[n-1])
			P.push_back(P[0]);
		return P;
	}

	size_t P0 {0};
	for (size_t i {1}; i < n; ++i)
		if (P[i].y() < P[P0].y() || (P[i].y() == P[P0].y() && P[i].x() > P[P0].x()))
			P0 = i;

	std::swap(P[P0], P[0]);
	const Vector pivot {P[0]};
	sort(P.begin() + 1, P.end(), [&pivot](const Vector& a, const Vector& b) {
			const Vector d1 {a - pivot};
			const Vector d2 {b - pivot};
			if (magnitude(d1 % d2) == 0) // are they collinear ?
				return magnitude(d1) < magnitude(d2); // return closest

			return std::atan2(d1.y(), d1.x()) < std::atan2(d2.y(), d2.x());
	});

	std::vector<Vector> S {P[n - 1], P[0], P[1]};
	size_t i {2};
	while (i < n) {
		size_t j {S.size() - 1};
		// test if ccw(S[j - 1], S[j], P[i]
		// (p - q) x (p - r) > 0
		if (magnitude((S[j-1] - S[j]) % (S[j - 1] - P[i])) > 0)
			S.push_back(P[i++]);
		else
			S.pop_back();
	}

	return S;
}
