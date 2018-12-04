#!/bin/bash
set -x
g++ -std=c++14 -O2 main.cpp  Vector.cpp Sphere.cpp  Line.cpp  Surface.cpp Tracer.cpp SurfacePlane.cpp Plane.cpp Linear.cpp SurfaceConvexPolygon.cpp ConvexPolygon.cpp
