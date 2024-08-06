#include <iostream>
#include <stdint.h>
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"


const double ratio = 16.0 / 9.0;
int cnt=4;
const double PI = 3.1415926535;
double albedo = 0.5;
double hit_sphere(const point3 &p, double rad,const ray &r){
    double a = dot(r.direction(), r.direction());
    double h = dot( r.direction() ,(p - r.origin()));
    double c = dot((p - r.origin()), (p - r.origin())) - rad * rad;
    double g = h * h -  a * c;
    if(g < 0)
        return -1.00;
    return (h - sqrt(g)) / a;
}
vec3 calculate_color(const ray &r,const hittable_list &h,int dep) {
    if(dep<=0)
        return color(0,0,0);
    hit_record rec;
    if(h.hit(r, 0.001,100000000.0, rec)){
   //     vec3 tar = rec.p + rec.normal + random_in_unit_sphere();
   //     return albedo * calculate_color(ray(rec.p, tar -
   //                 rec.p),h,dep-1 );
        vec3 att;
        ray scattered;
       // std::clog<<rec.mtr_ptr->albedo.x()<<std::endl;
        if(rec.mtr_ptr->scatter(r, rec, att, scattered)){

            //return color(0,0,0);
            return att*calculate_color(scattered, h, dep-1);
        }
        else return color(0,0,0);
        //return 0.5 * (tar - rec.normal +color(1,1,1));
    }
  //  double t = hit_sphere(point3(-0, -0, -1), 0.5, r);
  //  if(t > 0.0)
  //  {
  //      vec3 N = unit_vector(r.at(t) - vec3(-0,-0,-1));
  //      return 0.5 * color(N.x()+1, N.y()+1, N.z()+1);
  //  }
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return vec3(1.0, 1.0, 1.0) + ((vec3(0.5, 0.7, 1.0) -
           vec3(1.0, 1.0, 1.0)) * t);
//    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(1.0,
//            0.5, 0.0);
}
int main() {

    srand(time(0));
    // Image


    int image_width = 400;
    double foc = 3.0;
    int image_height = image_width / ratio;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ratio;
    std::clog<<"WIDTH "<<viewport_width<<"\n";
    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    vec3 horizontal(viewport_width, 0, 0);
    vec3 vertical(0, viewport_height, 0);
    vec3 origin(0, 0, 0.0);
    vec3 lower_left_corner =  -vertical * .5 - horizontal * 0.5 - vec3(0,0,foc);
    lower_left_corner.e[2] = -1;
    std::clog << lower_left_corner.x()<<"\n";
    std::clog << lower_left_corner.y()<<"\n";
    std::clog << lower_left_corner.z()<<"\n";

    hittable_list world;
    const auto a =
        make_shared<sphere>(point3(0.0,0.0,-1),0.5,make_shared<diffuse>(vec3(0.9,0.6,0.1)));
    const auto b = make_shared<sphere>(point3(0,-100.5,-1),
            100,make_shared<diffuse>(vec3(0.8,0.8,0.0)));
    const auto c =
        make_shared<sphere>(point3(-1,0.0,-1),0.5,make_shared<metal>(vec3(0.8,0.8,0.9)));
    const auto d = make_shared<sphere>(point3(1,0.0,-1),
            0.5,make_shared<metal>(vec3(0.8,0.8,0.9)));
 world.add(a);
   world.add(b);
 // world.add(c);
  //world.add(d);
   int sup=100;
    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            // Calculate u and v, the relative positions on the viewport
            vec3 color(0,0,0);
            for(int k=0;k<sup;k++)
            {
                float u = float(i+vec3::rand_d(-0.5,0.5)) / float(image_width);
                float v = float(j+vec3::rand_d(-0.5,0.5)) / float(image_height);

                // Compute the ray direction
                vec3 direction = lower_left_corner + u*horizontal + v*vertical ;
                direction = unit_vector(direction);
                ray r(origin, direction);

                // Determine the color based on the direction of the ray
                 color += calculate_color(r, world,50);
            }
            color /= double(sup);
            color = vec3(sqrt(color.x()), sqrt(color.y()), sqrt(color.z()));
           // Write the color to the image (details omitted)
            write_color(std::cout, color);
            cnt++;
        }
    }
    std::clog << "\rDone.                 \n";}
