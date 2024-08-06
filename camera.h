#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

const double ratio = 16.0 / 9.0;
class camera{
    camera(){
    image_width = 400;
    image_height = image_width / ratio;
    viewport_height = 2.0;
    viewport_width = viewport_height * ratio;
    horizontal = vec3(viewport_width, 0, 0);
    vertical = vec3(0, viewport_height, 0);
    origin = vec3(0, 0, 0);
    lower_left_corner =  -vertical * .5 - horizontal * 0.5;
    lower_left_corner.e[2] = -1;

    }
    ray get_ray(double u, double v){
        return ray(origin,lower_left_corner + u*horizontal + v*horizontal);
    }
    int image_width,image_height;
    double viewport_width,viewport_height;
    vec3 horizontal,vertical,origin,lower_left_corner;
};

#endif
