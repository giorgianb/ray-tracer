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
#        NSPHERES = 20
#        for radius in range(1, 5):
#            for i in range(NSPHERES):
#                x = radius * 100 * math.cos(2*math.pi * i/NSPHERES)
#                y = radius * 100 * math.sin(2*math.pi * i/NSPHERES)
#
#                colors = [(1, 0, 0), (0, 1, 0), (0, 0, 1)]
#                color = colors[i % len(colors)]
#
#                write_sphere(define_sphere(color, 50, x, y, 500 + i*100), file=f)
#


#        write_plane(define_plane_from_points((0, 0, 1), 
#            (200, -400, 400), 
#            (200, -400, 800),
#            (400, -400, 0)), file=f)
#
#        for x in range(-2, 3):
#            color = colors[abs(x) % len(colors)]
#
#            for z in range(-2, 8):
#                write_convex_polygon(define_convex_polygon_from_points(color,
#                    (x*200, -100, z*400),
#                    (x*200+50, -100, z*400),
#                    (x*200, -50, z*400),
#                    (x*200, -100, z*400)), file=f)
#
        NPOLY = 20
        for radius in range(1, 5):
            for i in range(NPOLY):
#                break
                theta = 2*math.pi*i/NPOLY

                xoff = radius * 100 * math.cos(theta)
                yoff = radius * 100 * math.sin(theta)
                zoff = 500+(radius*(NPOLY + 1)) + i
        
                dx1 = 100*math.cos(theta)
                dy1 = 100*math.sin(theta)
                dx2 = 100*math.cos(theta + math.pi/2)
                dy2 = 100*math.sin(theta + math.pi/2)

                p1 = (xoff + dx1, yoff + dy1, zoff)
                p2 = (xoff + dx2, yoff + dy2, zoff)
                p3 = (xoff, yoff, zoff)
                color = colors[abs(i) % len(colors)]
#                write_convex_polygon(
#                        define_convex_polygon_from_points(color, p1, p2, p3, p1), 
#                        file=f)
                print(roundt(p1), roundt(p2), roundt(p3), roundt(p1))
                write_polygon(
                        define_polygon_from_points(color, p1, p2, p3, p1), 
                        file=f)

#        radius = 0
#        theta = 0
#        xoff = radius * 100 * math.cos(theta)
#        yoff = radius * 100 * math.sin(theta)
#        zoff = 500+(radius*(NPOLY + 1)) + i
#        p1 = (100*math.cos(theta) + xoff, yoff, zoff)
#        p2 = (xoff, 100*math.sin(theta) + yoff, zoff)
#        p3 = (xoff, yoff, zoff)
#        color = colors[0]
#        write_polygon(
#                define_polygon_from_points(color, p1, p2, p3, p1), 
#                file=f)


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
