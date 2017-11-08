#ifndef MIXED_H
#define MIXED_H
#include "fraction.h"

using namespace std;

class mixed
{
    public:
    //const
        mixed();
        mixed(int whole);
        mixed(int n, int d);
//        mixed(int whole, int n = 0, int d = 1);
        mixed(double x);
    //destruct
//       ~mixed();
    //copy
        mixed(const fraction &other);
        mixed(const mixed &other);
    //assignment
        mixed& operator=(int x);
        mixed& operator=(double d);
        mixed& operator=(const fraction &other);
        mixed& operator=(const mixed &other);
    //math assignments
        mixed& operator+=(const mixed &other);
        mixed& operator-=(const mixed &other);
        mixed& operator*=(const mixed &other);
        mixed& operator/=(const mixed &other);
    //class member ops
//        mixed operator-() const; //Makes negative
//        mixed operator^(int x);


    private:
        fraction value;
        void mixed::copy(const mixed &other);
};

#endif // MIXED_H
