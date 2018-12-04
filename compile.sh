#!/bin/bash
set -x
g++ -o rt -std=c++14 -O2 src/main.cpp  src/Vector.cpp src/Sphere.cpp  src/Line.cpp  src/Surface.cpp src/Tracer.cpp src/SurfacePlane.cpp src/Plane.cpp src/Linear.cpp src/SurfaceConvexPolygon.cpp src/ConvexPolygon.cpp src/Debug.cpp -Iinclude/ 
