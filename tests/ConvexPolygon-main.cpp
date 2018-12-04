#include "ConvexPolygon.h"
#include "Plane.h"
#include "Line.h"
#include "Vector.h"

#include <iostream>

int main(void) {
	const Plane bp {{1, 0, 0}, {0, 1, 0}, {0, 0, -1}};
	const Line s1 {{1, 0, 0}, {0, 0, -1}};
	const Line s2 {{1, 0, 0}, {0, .5, -1}};
	const Line s3 {{0, 1, 0}, {0, 0, -1}};
	const Line s4 {{0, 1, 0}, {1, 0, -1}};
	const ConvexPolygon square {bp, {s1, s2, s3, s4}};

	const Plane bpt {{1, 0, 0}, {0, 1, 0}, {0, 0, -1}};
	const Line t1 {{1, 1, 0}, {-1, 0, -1}};
	const Line t2 {{1, -1, 0}, {+1, 0, -1}};
	const Line t3 {{1, 0, 0}, {0, 0, -1}};
	const ConvexPolygon triangle {bpt, {t1, t2, t3}};

	double x, y;
	while (std::cin >> x >> y) {
//		std::cout << '(' << x << ", " << y << ")\n";
//		std::cout << "Square: " << contains(square, {x, y, 0}) << '\n';
//		std::cout << "Triangle: " << contains(triangle, {x, y, 0}) << '\n';
//		std::cout << contains(triangle, {x, y, -1}) << '\n';
		std::cout << contains(square, {x, y, -1}) << '\n';

	}
}

