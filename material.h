#ifndef MATERIALH
#define MATERIALH
#include "ray.h"
#include "hittable.h"
#include "vec3.h"

struct hit_record;
class material{
public:
    virtual bool scatter(const ray &r_in,const hit_record &rec, vec3 &att, ray
            &scattered) const = 0;
};

class diffuse : public material {
    public:
        diffuse(const vec3 &a):albedo(a){}
 bool scatter(const ray &r_in,const hit_record &rec, vec3 &att, ray
            &scattered) const override{
        vec3 tar =  rec.normal + random_in_hemisphere(rec.normal);
        scattered = ray(rec.p, tar);
        att = albedo;
        return true;
    }
    vec3 albedo;
};
class metal: public material {
    public:
        metal(const vec3 &a):albedo(a){}
    bool scatter(const ray &r_in,const hit_record &rec, vec3 &att, ray
            &scattered) const override{
        vec3 tar = reflect(unit_vector(r_in.direction()),rec.normal);
        scattered = ray(rec.p, tar);
        att = albedo;
   // return dot(tar, rec.normal)>0;
     return true;
    return false;
    }

    vec3 albedo;
};

#endif
