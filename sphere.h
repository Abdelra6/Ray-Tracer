#ifndef SHPERE_H
#define SHPERE_H

#include "ray.h"
#include "hittable.h"
#include "vec3.h"
class material;
class sphere : public hittable{
    public :
        sphere();
        sphere(const point3 &center, double rad, shared_ptr<material>m):center(center),rad(rad), mtr_ptr(m){};
virtual bool hit(const ray &r, double ray_min,double ray_max, hit_record
                &rec) const;
        point3 center;
        double rad;
        shared_ptr<material>mtr_ptr;

};
inline bool sphere::hit(const ray &r, double ray_min,double ray_max, hit_record
                &rec)const {

            double a = dot(r.direction(), r.direction());
            double h = dot( r.direction() ,(center - r.origin()));
            double c = dot((center - r.origin()), (center - r.origin())) - rad * rad;
            double g = h * h -  a * c;

            if(g < 0)
                return false;

            double fi = (h - sqrt(g)) / a;
            double se = (h + sqrt(g)) / a;

            if(fi > ray_min && fi < ray_max)
            {
             rec.normal = unit_vector(r.at(fi) - center);
            //    if(dot(r.direction(), rec.normal)>0){
            //        rec.normal = -rec.normal;
            //    }
                rec.t = fi;
                rec.p = r.at(fi);
                rec.mtr_ptr = mtr_ptr;
                return true;
            }
            if(se > ray_min && se < ray_max)
            {
                rec.normal = unit_vector(r.at(se) - center);
            //    if(dot(r.direction(), rec.normal)>0){
            //        rec.normal = -rec.normal;
            //    }
                rec.t = se;
                rec.p = r.at(se);
                rec.mtr_ptr = mtr_ptr;
                return true;
            }
            //std::clog<<"FUCKKKKK"<<std::endl;
            return false;

        }

#endif
