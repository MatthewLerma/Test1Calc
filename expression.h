#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stack>
#include "mixed.h"
//#include "toRPN.h"
#include <vector>
#include <map>
//#include "fraction.h"

struct term
{
    fraction coef,power;
    term(fraction &c, fraction &p)
    {
        coef = c;
        power = p;
    }

    friend
    ostream& operator<<(ostream &out, const term &ter)
    {
        out << ter.coef;
        out << ter.power;
        return out;
    }
};



class expression
{
    public:
        expression();
        expression(const expression &other);
        ~expression();                        //Deconstructor

        expression(string &ExpStore); // Used for maps

        expression& operator=(const expression &other);



        expression& operator<<(const string &input);
//        expression& operator<<(expression &exp);

        void clear();
//        expression& derivative(unsigned int x = 1);

        fraction evaluateAt(const fraction &value);
        void tokenize();
        void Nocoeffcheck(string &token);
        void vectorizetokens();
        bool Negativecheck(fraction &c);

        friend
        ostream& operator<<(ostream &out, expression &exp);

        friend
        fraction operator^(expression &expres, fraction &evalnum);

        friend
        istream& operator>>(istream &in, expression &exp);

        //Expression addition/sub/mult for test

        friend
        expression operator+(expression &a, expression &b);

        friend
        expression operator-(expression &a, expression &b);

        friend
        expression operator*(expression &a, expression &b);

        friend
        expression operator % (expression &a, unsigned int x);


    private:
        vector<term> terms;
        vector<string> tokens;
        string ExpressionStore;
        map<string, int> precedence;
//        void loadMaps();
        void copy(const expression &other);
//        bool isOperator(const string &token) const;
        void trim(string &item);
        void Destroy();  //still needs to be fixed
        void consolidateExpression();
        void maketerms(const string &input);
        void makeNeg(); //Makes expression negative

};






#endif // EXPRESSION_H
