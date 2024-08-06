#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include <memory>
class material;


using std::make_shared;
using std::shared_ptr;

struct hit_record{
        point3 p;
        vec3 normal;
        double t;
 //       material *mtr_ptr;
        shared_ptr<material> mtr_ptr;

};

class hittable{
    public:
        virtual ~hittable() = default;
        virtual bool hit(const ray &r, double ray_min,double ray_max, hit_record& rec)
            const = 0;

};

#endif

