#include "RayUtils.h"
MaybeVector evaluate(const Ray& r, const double& s) {
	if (s >= 0)
		return {true, evaluate(Line {r.direction(), r.offset()}, s)};

	return {false, {0, 0, 0}};

}

Vector normal(const Ray& r, const Vector& v) {
	return normal(Line {r.direction(), r.offset()}, v);
}

Intersection intersection(const Ray& r, const Line& l) {
	auto [type, sol] = intersection(Line {r.direction(), r.offset()}, l);

	switch (type) {
		case LineLineIntersectionType::none:
			return EmptySet {};
		case LineLineIntersectionType::point:
			return ((r.offset() - sol) * r.direction()) >= 0 ?
				Intersection {sol} : Intersection {EmptySet {}};
		case LineLineIntersectionType::line:
			return r;
	}

}

Intersection intersection(const Ray& r, const Vector& v) {
	auto [type, sol] = intersection(Line {r.direction(), r.offset()}, v);

	switch (type) {
		case LineVectorIntersectionType::none:
			return EmptySet {};
		case LineVectorIntersectionType::point:
			return ((r.offset() - sol) * r.direction()) >= 0 ?
				Intersection {sol} : Intersection {EmptySet {}};

	}
}

