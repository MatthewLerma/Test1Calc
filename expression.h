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

class Term
{
    private:
    string e;
    string c;
    string v;
    string p;

    public:

    Term();

    void init(const string &strTerm);
    float evaluate(string val);
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
        void Nocoeffcheck(string &token);
        void vectorizetokens();
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
        void loadMaps();
        void copy(const expression &other);
        bool isOperator(const string &token) const;
        void tokenize();
        void trim(string &item);
        void Destroy();  //still needs to be fixed
};

class Character {
    public:
    static bool isDigit(char c) {
        return (isdigit(c) || (c=='-') || (c=='.'));
    }
    static bool isCharacter(char c) {
        return isalpha(c);
    }
    static bool isPower(char c) {
        return c == '^';
    }
};

class estack : public std::stack<string> {
public:
    using std::stack<string>::c; // expose the container
};

class Expression {
    public:
    string e;      // original expression
    estack postfix; // parsed to postfix notation
    Expression();
    void init(string expr);
    int priority(string oprtr);
    bool isOperator(string oprtr);
    float compute(string oprtr, string lOprnd, string rOprnd, string vValue);
    string evaluate(string vValue);
    void infixToPostfix();
};

#endif // EXPRESSION_H
