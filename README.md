# ray-tracer
Simple ray tracer written in C++

## Building
```
git clone https://github.com/giorgianb/ray-tracer
cd ray-tracer
./compile.sh
```
## Usage

To use the ray tracer, the light sources and the objects in the world need to be specified. These are stored in a text file. There are various objects that can be traced.

### Colors
Colors are specified using an `r g b` value which respectively specify the red, green, and blue values of the object. They must all be between `0` and `1`.

### Spheres
Spheres can be specified in the following manner:
```
Sphere
x y z radius r g b
```
Here, `x y z` are the coordinates of the center of the sphere, and `radius` is the radius of the sphere.

### Planes
Planes can be specified in the following manner:
```
Plane
ux uy uz vx vy vz ox oy oz r g b
```
Here, a plane is specified in the form of `s(ux, uy, uz) + t(vx, vy, vz) + (ox, oy, oz)`, where `(ox, oy, oz)` specify an offset and `(ux, uy, uz)` and `(vx, vy, vz)` are the direction vectors of the plane. In general, if you have the points `P`, `Q`, and `R` specifying a plane, `(ux, uy, uz)` can be defined as `PQ` (the vector from point `P` to point `Q`), `(vx, vy, vz)` can be defined as `PR` (the vector from point `P` to `R`), and `(ox, oy, oz)` can be specified as `R`.

### Polygons
Polygons can be specified in the following manner:
```
Polygon
ux uy uz vx vy vz ox oy oz
number_vertices
v1_x v1_y v1_z
v2_x v2_y v2_z
v3_x v3_y v3_z
...
vn_x vn_y vn_z
r g b
```
The first part specifies the plane that the polygon has on. It is specified in the same manner as mentioned above, in the `Plane` section: where the plane is specified in the form `s(ux, uy, uz) + t(vx, vy, vz) + (ox, oy, oz)`. Then, the number of vertices of the polygon is specified. **Important**: This will always be one more than the actual number of vertices of the Polygon. For example, if the you want to specify a triangle, the number of vertices will be 4. **This is because the first and last vertex must be the same.** Then, after the number of vertices is specified, the vertices are listed **in a counterclockwise manner**.

### Checkered Planes
Checkered Planes can be specified in the following manner:
```
CheckeredPlane
ux uy uz vx vy vz ox oy oz
number_colors
r1 g1 b1
r2 g2 b2
r3 g3 b3
rn gn bn
```
The checkered plane is specified in the same manner as mentioned in the `Plane` section: where the plane is specified in the form `s(ux, uy, uz) + t(vx, vy, vz) + (ox, oy, oz)`. Then, the number of colors is specified. What follows are the `r`, `g`, and `b` value of the colors. The size and shape of the "checker" is defined by the parallogram spanned by the vectors `(ux, uy, uz)` and `(vx, vy, vz)`.

### Point Light Sources
Point light sources are specified in the following manner:
```
PointLightSouce
x y z brightness
```
Here, `(x, y, z)` specify the location of the point light source. `brightness` specifies the brightness of the source. A good value is normally `2000000` although this highly depends on the distance of the light source from everything else. 

### Sample Usage
magenta-sphere.rt:
```
Sphere
0 0 500	50 	1 0 1
PointLightSource
500 200 0 300000
PointLightSource
-500 -200 0 50000
```

`./rt --file=magenta-sphere.rt --out=magenta-sphere.ppm`
