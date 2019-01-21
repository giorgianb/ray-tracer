#!/bin/bash
set -x
g++ -o rt -std=c++17 -O2 src/main.cpp src/Sphere.cpp src/Surface.cpp src/Tracer.cpp src/SurfacePlane.cpp src/Linear.cpp src/SurfacePolygon.cpp src/Polygon.cpp src/PolygonUtils.cpp src/LightSource.cpp src/PointLightSource.cpp src/Debug.cpp src/CheckeredPlane.cpp -Iinclude/ 
