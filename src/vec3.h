#ifndef VEC3_H
#define VEC3_H
#include <cmath>
#include <iostream>

class Vec3 {
public:
    Vec3() : e{0, 0, 0} {}
    Vec3(double e_x, double e_y, double e_z) : e{e_x, e_y, e_z} {}

    double x() const {
        return e[0];
    }

    double y() const {
        return e[1];
    }

    double z() const {
        return e[2];
    }



    double e[3];
};



#endif
