
//		if (m.transparency > 0) {
//			// refract AND reflect, scale by refraction by transparancy and add to color
//			const Material m {s->material(*hit)};
//			const double n1 {1};
//			const double t1 {theta(normal, ray)};
//			const double n2 {m.refractivity};
//			// Dealth with total internal reflection later
//			if (n1/n2 * std::sin(t1) > 1)
//				return color;
//
//			const double t2 {snell(n1, t1, n2)};
//
//			// deal with reflected portion
//			const double reflectivity {fresnel(n1, t1, n2, t2)};
//			const Ray rf {with_bias(reflect(s->normal(*hit, ray.offset()), ray))};
//			const Color rc {trace(rf, ll, sl)};
//			color.r += rc.r * reflectivity;
//			color.b += rc.b * reflectivity;
//			color.g += rc.g * reflectivity;
//
//			// deal with refracted portion
//			const Ray rt {refract(normal, ray, n1, t1, n2, t2)};
//			if (const auto out = s->transmit(rt)) {
//				// TODO: for now we will assume that the surface is made out of
//				// a uniform material and thus theta_in = theta_out
//				const Ray rt {with_bias({ray.direction(), *out})};
//				const Color rc {trace(rt, ll, sl)};
//				color.r += rc.r * m.transparancy * (1 - reflectivity);
//				color.b += rc.b * m.transparancy * (1 - reflectivity);
//				color.g += rc.g * m.transparancy * (1 - reflectivity);
//			}
//		}
	}


