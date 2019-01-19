#!/bin/bash
set -x
g++ -o rt -std=c++17 -O2 src/main.cpp src/Sphere.cpp src/Surface.cpp src/Tracer.cpp src/SurfacePlane.cpp src/Linear.cpp src/SurfaceConvexPolygon.cpp src/ConvexPolygon.cpp src/SurfacePolygon.cpp src/Polygon.cpp src/PolygonUtils.cpp src/Debug.cpp src/ConvexPolygonUtils.cpp -Iinclude/ 
