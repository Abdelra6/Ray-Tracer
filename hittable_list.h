#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H


#include "hittable.h"
#include <vector>

class hittable_list:public hittable{
    public:
        std::vector<shared_ptr<hittable>> objects;
        hittable_list(){}
        void clear(){
            objects.clear();
        }
        void add(shared_ptr<hittable>o) {
            objects.push_back(o);
        }
        bool hit(const ray &r, double ray_min,double ray_max, hit_record
                &rec)const override{
            hit_record tmp;
            bool hit_anything = false;
            double closest = ray_max;

            for(const auto &a:objects){
                if(a->hit(r, ray_min, closest, tmp)){
                    hit_anything = true;
                    closest = tmp.t;
                    rec = tmp;
                }
            }
            return hit_anything;
        }
};

#endif
