#include "RayUtils.h"
#include "LineUtils.h"

MaybeVector evaluate(const Ray& r, const double& s) {
	if (s >= 0)
		return {true, evaluate(Line {r.direction(), r.offset()}, s)};

	return {false, {0, 0, 0}};

}

Vector normal(const Ray& r, const Vector& v) {
	return normal(Line {r.direction(), r.offset()}, v);
}

Intersection intersection(const Ray& r, const Line& l) {
	const Intersection inter {intersection(Line {r.direction(), r.offset()}, l)};

	if (const auto solp = std::get_if<Vector>(&inter))
		return ((*solp - r.offset()) * r.direction()) >= 0 ?
			Intersection {*solp} : Intersection {EmptySet {}};
	else if (std::holds_alternative<Line>(inter))
		return r;
	else
		return EmptySet {};
}

Intersection intersection(const Ray& r, const Vector& v) {
	const Intersection inter {intersection(Line {r.direction(), r.offset()}, v)};

	if (const auto solp = std::get_if<Vector>(&inter))
		return ((*solp - r.offset()) * r.direction()) >= 0 ?
			Intersection {*solp} : Intersection {EmptySet {}};
	else
		return EmptySet {};
}
