#include "mixed.h"

mixed::mixed()
{

}

mixed::mixed(int whole)
{
    value = whole;
}

mixed::mixed(int n, int d)
{
    value = n/d;

}

//mixed::mixed(int whole, int n = 0, int d = 1)
//{
//    value = whole;
//}

mixed::mixed(double x)
{

}

mixed::mixed(const fraction &other)
{
    value = other;
}

mixed& mixed::operator=(int x)
{
    value = x;
    return *this;
}

mixed& mixed::operator=(double d)
{
    value = d;
    return *this;
}


mixed& mixed::operator=(const fraction &other)
{
    value = other;
    return *this;
}

mixed& mixed::operator=(const mixed &other)
{
    if(&other != this)
    {
        value = other.value;
    }
    return *this;
}

void mixed::copy(const mixed &other)
{
    value = other.value;
}

mixed&mixed::operator+=(const mixed &other)
{
    mixed a;
    return a;
}

mixed&mixed::operator-=(const mixed &other)
{
    mixed a;
    return a;
}

mixed&mixed::operator*=(const mixed &other)
{
    mixed a;
    return a;
}

//mixed& operator/(const mixed &other)
//{
//    mixed a;
//    return a;
//}

//mixed operator-() const;
//{
//    mixed a;
//    return a;
//}
//mixed operator^(int x)
//{

//}
