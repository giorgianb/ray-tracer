#!/bin/bash
set -x
g++ -o rt -std=c++17 -O2 src/main.cpp  src/Vector.cpp src/Sphere.cpp  src/Line.cpp  src/Surface.cpp src/Tracer.cpp src/SurfacePlane.cpp src/Plane.cpp src/Linear.cpp src/SurfaceConvexPolygon.cpp src/ConvexPolygon.cpp src/SurfacePolygon.cpp src/Polygon.cpp src/PolygonUtils.cpp src/LineSegmentUtils.cpp src/RayUtils.cpp src/LineSegment.cpp src/Ray.cpp src/Debug.cpp src/LineUtils.cpp src/PlaneUtils.cpp src/ConvexPolygonUtils.cpp -Iinclude/ 
