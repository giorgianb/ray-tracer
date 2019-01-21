#!/usr/bin/python3
import sys
from random import randrange
import math

def roundt(t):
    l = []
    for i in t:
        l.append(round(i, 3))
    return tuple(l)

def main():
    colors = [(1, 0, 0), (0, 1, 0), (0, 0, 1)]
    with open(sys.argv[1], 'w') as f:


def scale(k, v):
    return tuple(k*e for e in v)

def add(u, v):
    return tuple(sum(z) for z in zip(u, v))

def define_sphere(color, radius, x, y, z):
    return ((x, y, z, radius), color)

def write_sphere(sphere, file=sys.stdout):
    print("Sphere", file=file)
    # syntax for sphere
    x, y, z, radius = sphere[0]
    print("{} {} {}\t{}\t{} {} {}".format(*sphere[0], *sphere[1]), file=file)


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
