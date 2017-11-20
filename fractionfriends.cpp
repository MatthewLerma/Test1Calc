#include "fraction.h"



ostream& operator<<(ostream &out, const fraction &me)
{
    out<<me.num;
    if(me.denom != 1)
        cout<<"/"<<me.denom;
    return out;
}

istream& operator>>(istream &in, fraction &me)
{
    char junk;
    double value;
    me.denom = 1;
    in>>me.num;
    if(in.peek() == '/')
        in>>junk>>me.denom;
    else
        if(in.peek() == '.')
        {
            in.putback(me.num);
            in>>value;
            me = value;
        }
    me.reduce();
    return in;
}

fraction operator*(const fraction &a, const fraction &b)
{
    int num, denom;
    fraction c;
    num = a.num * b.num;
    denom = a.denom * b.denom;
    c.setValue(num,denom);
    return c;
}

fraction operator/(const fraction &a, const fraction &b)
{
    int num, denom;
    fraction c;
    num = a.num * b.denom;
    denom = a.denom * b.num;
    c.setValue(num,denom);
    return c;
}

fraction operator+(const fraction &a, const fraction &b)
{
    int num, denom;
    fraction c;
    num = a.num * b.denom + a.denom * b.num;
    denom = a.denom * b.denom;
    c.setValue(num,denom);
    return c;
}

fraction operator-(const fraction &a, const fraction &b)
{
 /*
    int num, denom;
    fraction c;
    num = a.num * b.denom - a.denom * b.num;
    denom = a.denom * b.denom;
    c.setValue(num,denom);
    return c;
*/
    fraction c;
    c = a + -b;
    return c;
}

bool operator!=(const fraction &a, const fraction &b)
{
    return !(a == b);
}


bool operator==(const fraction &a, const fraction &b)
{
    return a.num * b.denom == a.denom * b.num;
}


bool operator>=(const fraction &a, const fraction &b)
{
    return a.num * b.denom >= a.denom * b.num;
}


bool operator<=(const fraction &a, const fraction &b)
{
    return a.num * b.denom <= a.denom * b.num;
}


bool operator>(const fraction &a, const fraction &b)
{
    return !(a <= b);
}


bool operator<(const fraction &a, const fraction &b)
{
    return !(a >= b);
}

fraction abs(const fraction &other)
{
    fraction answer(abs(other.num), other.denom);
    return answer;
}

double doub(const fraction &other){
    return other.num/other.denom;
}


fraction sqrt(const fraction &other)
{
    return other;
}
