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

//#include "debug.h"
bool contains(const ConvexPolygon& p, const Vector& tp) {
	std::vector<Vector> points {tp};
	// find intersection of line with slope of edge perpendicular and offset of tp with edge
	for (const auto& edge: p.edges()) {
		const Line perp {normal(edge, normal(p.plane())), tp};
		const LineLineIntersection pi {intersection(edge, perp)}; // polygon intersection
		// TODO: figure out what to do if it's a line
		if (pi.first == LineLineIntersectionType::none)
			return false;

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
				{-p.plane().offset().x() + point.x()},
				{-p.plane().offset().y() + point.y()},
				{-p.plane().offset().z() + point.z()}
			}
		};
//		std::cout << "coordinate matrix: " << '\n';
//		std::cout << am.first << '\n' << am.second << '\n';
		const SolutionSet s {solution(rref(am))};
		assert(s.first == SolutionSetType::unique);
		assert(std::fabs(s.second[2][0]) <= ESP);
		const Vector planepoint {s.second[0][0], s.second[1][0], 0};
//		std::cout << "coordinate matrix solution: " << '\n';
//		std::cout << am.first << '\n' << am.second << '\n';
//		std::cout << "coordinate of " << point << " in plane " << p.plane() << ": ";
//		std::cout << planepoint << '\n';
		plane_points.push_back(planepoint);
	}
//	plane_points.push_back(plane_points.front()); // for the CH algorithm

//	std::cout << "without hull: ";
//	for (const auto& p: plane_points)
//		std::cout << p << ' ';
//	std::cout << '\n';
	const std::vector<Vector> ch {convex_hull(plane_points)};

//	std::cout << "with hull: ";
//	for (const auto& p: ch)
//		std::cout << p << ' ';
//	std::cout << '\n';

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
//	std::cout << "sorted with respected to pivot: ";
//	for (const auto& p: P)
//		std::cout << p << ' ';
//	std::cout << '\n';

	std::vector<Vector> S {P[n - 1], P[0], P[1]};

	size_t i {2};
	while (i < n) {
		size_t j {S.size() - 1};
		assert(S.size() > 1);
		// test if ccw(S[j - 1], S[j], P[i]
		// (q - p) x (r - p) > 0
		bool ccw {((S[j] - S[j-1]) % (P[i] - S[j-1])).z() > 0};

//		std::cout << P[i] << " to the left of " << S[j-1] << " -> " << S[j] << ": ";
//		std::cout << ccw << '\n';
		const Vector v1 {S[j] - S[j-1]};
		const Vector v2 {P[i] - P[i - 1]};
//		std::cout << v1 << "x" << v2 << " = " << magnitude(v1 % v2) << '\n';

		

		if (ccw)		
			S.push_back(P[i++]);
		else
			S.pop_back();
	}

	return S;
}
