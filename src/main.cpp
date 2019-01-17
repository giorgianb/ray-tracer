#include "Tracer.h"
#include "Surface.h"
#include "Sphere.h"
#include "SurfacePlane.h"
#include "Line.h"
#include "SurfaceConvexPolygon.h"
#include "SurfacePolygon.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <getopt.h>

// TODO: remove, only included for debugging purposes
#include <set>
#include "Debug.h"

SurfaceList read_surfaces(std::istream& in);

enum command_line_options
{
	input_file, output_file, x_resolution, y_resolution, 
	x_min, x_max, y_min, y_max, offset, eye_x, eye_y, eye_z, brightness, help
};


int main(int argc, char *argv[]) {
	static const struct option long_options[] {
		{"file", required_argument, nullptr, input_file},
		{"out", required_argument, nullptr, output_file},
		{"x-res", required_argument, nullptr, x_resolution},
		{"y-res", required_argument, nullptr, y_resolution},
		{"x-min", required_argument, nullptr, x_min},
		{"x-max", required_argument, nullptr, x_max},
		{"y-min", required_argument, nullptr, y_min},
		{"y-max", required_argument, nullptr, y_max},
		{"offset", required_argument, nullptr, offset},
		{"eye-x", required_argument, nullptr, eye_x},
		{"eye-y", required_argument, nullptr, eye_y},
		{"eye-z", required_argument, nullptr, eye_z},
		{"brightness", required_argument, nullptr, brightness},
		{"help", no_argument, NULL, help},
		{0, 0, 0, 0}
	};

	const char *file_name {nullptr};
	const char *output_file_name {"out.ppm"};
	ResSpec resolution {1000, 1000};
	double plane_offset {250};
	Corner lower {-100, -100};
	Corner upper {100, 100};
	Vector eye {0, 0, -250};
	double b {2e6};
	for (;;) {
		int option_index {0};

		const int c {getopt_long(argc, argv, "", long_options, &option_index)};
		if (c == -1)
			break;

		switch (c) {
			case input_file:
				file_name = optarg;
				break;
			case output_file:
				output_file_name = optarg;
				break;
			case x_resolution:
				sscanf(optarg, "%zu", &resolution.first);
				break;
			case y_resolution:
				sscanf(optarg, "%zu", &resolution.second);
				break;
			case x_min:
				sscanf(optarg, "%d", &lower.first);
				break;
			case x_max:
				sscanf(optarg, "%d", &upper.first);
				break;
			case y_min:
				sscanf(optarg, "%d", &lower.second);
				break;
			case y_max:
				sscanf(optarg, "%d", &upper.second);
				break;
			case offset:
				sscanf(optarg, "%lf", &plane_offset);
				break;
			case eye_x:
				int x;
				sscanf(optarg, "%d", &x);
				eye.x(x);
				break;
			case eye_y:
				int y;
				sscanf(optarg, "%d", &y);
				eye.y(y);
				break;
			case eye_z:
				int z;
				sscanf(optarg, "%d", &z);
				eye.z(z);
				break;
			case brightness:
				sscanf(optarg, "%lf", &b);
				break;
			case help:
			{
				static const char *const help_message = 
				"--file, --file=\t\t\tRead shapes from specified file.\n"
				"--out, --out=\t\t\tOutput ray-traced image to specified file.\n"
				"--x-res, --x-res=\t\tSpecifies x-resolution.\n"
				"--y-res, --y-res=\t\tSpecifies y-resoltuion.\n"
				"--x-min, --x-min=\t\tSpecifies minimum x-coordinate of viewing plane.\n"
				"--x-max, --x-max=\t\tSpecifies maximum x-coordinate of viewing plane.\n"
				"--y-min, --y-min=\t\tSpecifies minimum y-coordinate of viewing plane.\n"
				"--y-max, --y-max=\t\tSpecifies maximum y-coordinate of viewing plane.\n"
				"--offset, --offset=\t\tSpecifies offset of viewing plane.\n"
				"--eye-x, --eye-x=\t\tSpecifies x-coordinate of eye.\n"
				"--eye-y, --eye-y=\t\tSpecifies y-coordinate of eye.\n"
				"--eye-z, --eye-z=\t\tSpecifies z-coordinate of eye.\n"
				"--brightness, --brightness=\tSpecifies brightness.\n\n\n"
				"If no input file is provided, shapes are read from standard input.";
				std::cout << help_message << '\n';

				std::exit(0);

				break;

			}
		}
	}

	std::cout << "Reading from ";
	if (file_name)
		std::cout << file_name;
	else
		std::cout << "standard input";
	std::cout << "...\n";

	std::cout << "Writing image to " << output_file_name << '\n';

	std::cout << "Resolution: (" << resolution.first << ", " << resolution.second << ")\n";
	std::cout << "Viewing Plane: (" << lower.first << ", " << lower.second << ") -> ("
		<< upper.first << ", " << upper.second << ")\n";
	std::cout << "Viewing Plane " << plane_offset << " in front of the eye.\n";
	std::cout << "Eye located at: (" << eye.x() << ", " << eye.y() << ", " << eye.z() << ")\n";
	std::cout << "Brightness: " << b << '\n';

	SurfaceList world;
	if (file_name) {
		std::ifstream in {file_name};
		world = read_surfaces(in);
	} else
		world = read_surfaces(std::cin);

	const PPMImage traced {trace(world, eye, resolution, lower, upper, plane_offset, b)};

	std::ofstream out {output_file_name};
	out << "P3 " << resolution.first << ' ' << resolution.second << ' ' << 255 << '\n';
	for (size_t j = 0; j < resolution.second; ++j)
		for (size_t i = 0; i < resolution.first; ++i)
			out << (int) traced[i][j].r << ' '
				<< (int) traced[i][j].b << ' '
				<< (int) traced[i][j].g << '\n';
	return 0;
}

SurfaceList read_surfaces(std::istream& in)
{
	SurfaceList l;
	std::string shape;
	while (in >> shape) {
		if (shape == "Sphere") {
			double pos_x, pos_y, pos_z, radius, r, g, b;
			in >> pos_x >> pos_y >> pos_z >> radius >> r >> g >> b;
			l.push_back(new Sphere {Vector {pos_x, pos_y, pos_z}, radius, {r, g, b}});
		} else if (shape == "Plane") {
			double ux, uy, uz, vx, vy, vz, ox, oy, oz, r, g, b;
			in >> ux >> uy >> uz >> vx >> vy >> vz >> ox >> oy >> oz >> r >> g >> b;
			l.push_back(new SurfacePlane 
					{{{ux, uy, uz}, {vx, vy, vz}, {ox, oy, oz}}, {r, g, b}});
		} else if (shape == "ConvexPolygon") {
			double ux, uy, uz, vx, vy, vz, ox, oy, oz;

			in >> ux >> uy >> uz >> vx >> vy >> vz >> ox >> oy >> oz;
			const Plane base {{ux, uy, uz}, {vx, vy, vz}, {ox, oy, oz}};

			size_t nedges;
			in >> nedges;

			std::vector<Line> edges;
			for (size_t i {0}; i < nedges; ++i) {
				double vx, vy, vz, ox, oy, oz;
				in >> vx >> vy >> vz >> ox >> oy >> oz;
				edges.push_back({{vx, vy, vz}, {ox, oy, oz}});
			}

			double r, g, b;
			in >> r >> g >> b;
			l.push_back(new SurfaceConvexPolygon {{base, edges}, {r, g, b}});
		} else if (shape == "Polygon") {
			double ux, uy, uz, vx, vy, vz, ox, oy, oz;

			in >> ux >> uy >> uz >> vx >> vy >> vz >> ox >> oy >> oz;
			const Plane base {{ux, uy, uz}, {vx, vy, vz}, {ox, oy, oz}};

			size_t nvertices;
			in >> nvertices;

			PointSet vertices;
			for (size_t i {0}; i < nvertices; ++i) {
				double vx, vy, vz;
				in >> vx >> vy >> vz;
				vertices.push_back({vx, vy, vz});
			}


			double r, g, b;
			in >> r >> g >> b;

			const Polygon tmp {base, vertices};
			const PointSet p_vertices {tmp.vertices()};

			const std::set<Vector> test_set {p_vertices.begin(), p_vertices.end()};
			if (test_set.size() <= 2) {
				std::cerr << "SIZE: " << test_set.size() << '\n';
				std::cerr << "raw: ";
				for (const auto& t: vertices)
					std::cerr << t << ' ';
				std::cerr << '\n';

				std::cerr << "filtered: ";
				for (const auto& t: p_vertices)
					std::cerr << t << ' ';
				std::cerr << '\n';

				std::cerr << "filtered+unique: ";
				for (const auto& t: test_set)
					std::cerr << t << ' ';
				std::cerr << '\n';

				std::cerr << "line segments: ";
				for (const auto& t: tmp.edges())
					std::cerr << t << '\n';


				continue;
			}

			std::cerr << "Polygon Vertices:\n";
			for (const auto& t: tmp.vertices())
				std::cerr << t << ' ';
			std::cerr << '\n';

			std::cerr << "Polygon Edges:\n";
			for (const auto& t: tmp.edges())
				std::cerr << t << '\n';
			std::cerr << '\n';


			l.push_back(new SurfacePolygon {{base, vertices}, {r, g, b}});
		}
	}

	return l;
}
