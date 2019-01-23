#!/usr/bin/python3
import sys
from random import randrange
import math

def rgb(r, g, b):
    return (r / 255.0, g / 255.0, b / 255.0)

def roundt(t):
    l = []
    for i in t:
        l.append(round(i, 3))
    return tuple(l)

def rotate_xz(x, y, z, theta):
    return [x*math.cos(theta) + z*-math.sin(theta), 
            1,
            x*math.sin(theta) + z*math.cos(theta)]

def main():
    colors = [
            rgb(255, 0, 0), 
            rgb(255, 127, 0), 
            rgb(255, 255, 0), 
            rgb(0, 255, 0), 
            rgb(0, 0, 255),
            rgb(139, 0, 255)
            ]
    with open(sys.argv[1], 'w') as f:
        print("""
PointLightSource
0 0 -250 2000000
""", file=f)
        print("""
PointLightSource
0 0 1250 4000000
""", file=f)
        print("""
PointLightSource
0 0 2000 4000000
""", file=f)
        print("""
PointLightSource
0 0 4000 8000000
""", file=f)

 
        print("""
CheckeredPlane
200 0 -400	0 0 400		200 -1000 400
3
0 0 0 1 1 1 0
1 0 0 0 1 0 1
0 0 0 1 0 1 1""", file=f)
        print("""
CheckeredPlane
100 0 -100	0 0 100		200 400 400
3
0 0 0 1 1 0 0
0 0 0 1 0 1 0
0 0 0 1 0 0 1""", file=f)

        # Fill in
        write_sphere
        radius = 300
        NSPHERES = 20
        for i in range(NSPHERES):
            theta = i * 2*math.pi / NSPHERES
            pos =  rotate_xz(
                    radius * math.cos(theta),
                    radius * math.sin(theta),
                    0,
                    math.pi/4
                    )

            pos[2] += 1000

            write_sphere(
                    define_sphere(
                        define_material(
                            .5, # reflectivity
                            0, # refractivity
                            0, # transparancy
                            .5, # diffusivity
                            colors[i % len(colors)]
                        ), 
                        50, # radius
                        *pos
                    ),
                    f
            )

            pos = rotate_xz(
                    0,
                    radius * math.cos(theta),
                    radius * math.sin(theta),
                    math.pi/4)

            pos[2] += 1000

            write_sphere(
                    define_sphere(
                        define_material(
                            .25, # reflectivity
                            0, # refractivity
                            0, # transparancy
                            .75, # diffusivity
                            colors[i % len(colors)]
                        ), 
                        50, # radius
                        *pos
                        ),
                    f
            )
#
#        write_sphere(
#                define_sphere(
#                    define_material(
#                            0, # reflectivity
#                            0, # refractivity
#                            0, # transparancy
#                            1, # diffusivity
#                            colors[0] # shouldn't matter
#                        ), 
#                    50, # radius
#                    0,
#                    0,
#                    1000
#                ),
#                f
#        )

#        write_sphere(
#                define_sphere(
#                    define_material(
#                            1, # reflectivity
#                            0, # refractivity
#                            0, # transparancy
#                            0, # diffusivity
#                            colors[0] # shouldn't matter
#                        ), 
#                    250, # radius
#                    0,
#                    0,
#                    1000
#                ),
#                f
#        )
#
def scale(k, v):
    return tuple(k*e for e in v)

def add(u, v):
    return tuple(sum(z) for z in zip(u, v))

def define_color(r, g, b):
    return (r, g, b)

def define_material(
        reflectivity,
        refractivity,
        transparancy,
        diffusivity,
        color):
    return (reflectivity, refractivity, transparancy, diffusivity, color)

def define_sphere(material, radius, x, y, z):
    return ((x, y, z, radius), material)

def write_sphere(sphere, file=sys.stdout):
    print("Sphere", file=file)
    # syntax for sphere
    x, y, z, radius = sphere[0]
    print("{} {} {}\t{}".format(*sphere[0]), file=file)
    write_material(sphere[1], file)

def write_color(color, file=sys.stdout):
    print("{} {} {}".format(*color), file=file)

def write_material(material, file=sys.stdout):
    print("{} {} {} {}".format(*material[:4]), file=file)
    write_color(material[4], file)

def define_plane_from_points(color, p1, p2, p3):
    u = add(p3, scale(-1, p1))
    v = add(p2, scale(-1, p1))
    o = p1
    return (u + v + o, color)

def write_plane(plane, file=sys.stdout):
    print("Plane", file=file)
    # syntax for plane
    ux, uy, uz, vx, vy, vz, ox, oy, oz = plane[0]
    print("{} {} {}\t{} {} {}\t{} {} {}\t{} {} {}".format(*plane[0], *plane[1]), file=file)

def define_convex_polygon_from_points(color, *points):
    assert len(points) >= 4
    assert points[0] == points[-1]

    base = define_plane_from_points(color, *points[:3])[0]

    edges = []
    for i in range(len(points) - 1):
        edges.append(add(points[i+1], scale(-1, points[i])) + points[i])

    return ((base, tuple(edges)), color)

def define_polygon_from_points(color, *points):
    assert len(points) >= 4
    assert points[0] == points[-1]

    base = define_plane_from_points(color, *points[:3])[0]
    return ((base, tuple(points)), color)


def write_convex_polygon(convex_polygon, file=sys.stdout):
    print("ConvexPolygon", file=file)
    base, edges = convex_polygon[0]
    print("{} {} {}\t{} {} {}\t{} {} {}".format(*base), file=file)
    print(len(edges), file=file)
    for edge in edges:
        print("{} {} {}\t{} {} {}".format(*edge), file=file)

    print("{} {} {}".format(*convex_polygon[1]), file=file)

def write_polygon(polygon, file=sys.stdout):
    print("Polygon", file=file)
    base, vertices = polygon[0]
    print("{} {} {}\t{} {} {}\t{} {} {}".format(*base), file=file)
    print(len(vertices), file=file)
    for vertex in vertices:
        print("{} {} {}".format(*vertex), file=file)

    print("{} {} {}".format(*polygon[1]), file=file)


if __name__ == '__main__':
    main()
