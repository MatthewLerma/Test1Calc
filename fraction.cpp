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


fraction::fraction(double x)  //not properly handeling doubles
{
    int pos = 0, power;
    string temp, lengthtest;
    stringstream ss;
    ss << x;
    getline(ss,temp);
    ss.str("");
    ss.clear();
    lengthtest = temp.substr((pos = temp.find(".")));
    power = pow(10,lengthtest.size());
    num = x * power;
    denom = power;
    reduce();
}

fraction::fraction(string &input)
{
    int pos = 0, n=0, d=0;
    stringstream temp;
    double dubinput;
    if((pos=input.find_first_of("."))<input.size())
    {
        temp << input;
        temp >> dubinput;
        temp.str("");
        temp.clear();
        *this = dubinput;
    }
    else if((pos=input.find_first_of("/"))<input.size())
    {
        temp << input.substr(0,pos);
        temp >> n;
        temp.str("");
        temp.clear();
        temp << input.substr(pos + 1);
        temp >> d;
        temp.str("");
        temp.clear();
        num = n;
        denom = d;
    }
    else
    {
        temp << input;
        temp >> n;
        temp.str("");
        temp.clear();
        num = n;
        denom = 1;
    }
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

fraction operator^(fraction &cof, fraction &po)
{
    double newpow;
    newpow = toDouble(po);
    cof.num = pow(cof.num,newpow);
    if(!(cof.denom == 0))
        cof.denom = pow(cof.denom,newpow);
    return cof;
}

double toDouble(fraction &makedub)
{
    double n = makedub.num,d = makedub.denom;
    return (n/d);
}

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


