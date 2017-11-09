#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "mixed.h"
//#include "toRPN.h"
#include <vector>
#include <map>
//#include "fraction.h"

struct term
{
    fraction coef,power;
};

class expression
{
    public:
        expression();
        expression(const expression &other);
        ~expression();                        //Deconstructor

        expression(const string  &infix); // Used for maps

        expression& operator=(const expression &other);
        expression& operator<<(const string &input);
//        bool goodExpression();
        expression& derivative(unsigned int x = 1);
//        fraction evaluateAt(const fraction &value);

//        friend
//        ostream& operator<<(ostream &out, const expression &exp);

//        friend
//        istream& operator>>(istream &in, expression &exp);

    private:
        //string expressionToStore;   //dont think I need this
        vector<term> terms;
        vector<string> tokens;
        string inFix,postFix, operators;
        map<string, int> precedence;
        void expression::loadMaps();
        void copy(const expression &other);
        bool isOperator(const string &token) const;
        void expression::tokenize();
        void expression::trim(string &item);
        void expression::Destroy();  //still needs to be fixed
};

#endif // EXPRESSION_H
