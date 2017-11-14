#include "fraction.h"

fraction::fraction()
{
    num = 0;
    denom = 1;
}

fraction::fraction(int n) //The "one argument" constructor
{
    num = n;
    denom = 1;
}

fraction::fraction(int n, int d) //The "two argument" constructor
{
    num = n;
    denom = d;
    reduce();
}


fraction::fraction(double x)
{
    int tempNum = (int)x, temp = 0;
    double frac = x - tempNum;
    int power = 1;
    while(frac != 0)
    {
        temp *= 10 + (int)(frac * 10);
        frac = frac*10 - (int)(frac * 10);
        power *= 10;
    }
    num = tempNum * power + temp;
    denom = power;
    reduce();
}

fraction::~fraction() //Destructor
{
    num = denom = 0;
}

fraction::fraction(const fraction &other)//Copy constructor
{
    num = other.num;
    denom = other.denom;
}

fraction& fraction::operator=(const fraction &other)//Assignment operator
{
    if(&other != this)
    {
        num = other.num;
        denom = other.denom;
    }
    return *this;
}

fraction& fraction::operator-=(const fraction &other)//subtracts someone to me
{
    num = num*other.denom - other.num*denom;
    denom *= other.denom;
    reduce();
    return *this;
}

fraction& fraction::operator*=(const fraction &other)//multiplies someone to me
{
    num *= other.num;
   denom *= other.denom;
   reduce();
   return *this;
}

fraction& fraction::operator/=(const fraction &other)//divides someone to me
{
    num *= other.denom;
    denom *= other.num;
    reduce();
    return *this;
}

fraction& fraction::operator+=(const fraction &other)//add someone to me
{
    //a += 3;
    num = num*other.denom + other.num*denom;
    denom *= other.denom;
    reduce();
    return *this;
}

fraction fraction::operator-() const
{
    fraction c(-num,denom);
    return c;
}

//fraction fraction::operator^(int x)
//{
//
//}
//
//double fraction::toDouble()
//{
//
//}

int fraction::getNum() const
{
    return num;
}

int fraction::getDenom() const
{
    return denom;
}

void fraction::setValue(int n, int d)
{
    num = n;
    denom = d;
    reduce();
}

void fraction::display()
{
    cout<<num<<"/"<<denom;
}

int fraction::gcd(int p, int q)
{
    return q==0 ? p : gcd(q,p%q);
}

void fraction::reduce()
{
    int div = gcd(num, denom);
    num /= div;
    denom /= div;
    if(denom < 0)
    {
        num = -num;
        denom = -denom;
    }
}
