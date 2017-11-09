#include "expression.h"

expression::expression() : operators("+-")
{
    loadMaps();
}

expression::expression(const string  &infix): operators("+-")
{
    inFix = infix;
    loadMaps();
}
void expression::loadMaps()
{
    precedence["+"] = precedence["-"] = 1;
}


expression::expression(const expression &other)
{
    copy(other);
}

expression::~expression()
{
    //Destroy();
    terms.clear();
}

expression& expression::operator=(const expression &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

void expression::copy(const expression &other)
{
    for (unsigned int i = 0; i < other.terms.size();++i)
    {
        terms[i] = other.terms[i];
    }
}

bool expression::isOperator(const string &token) const
{
    return token.find_first_of(operators) < token.size();
}

void expression::tokenize()
{
    //str.replace(sizeofstringinputting(2), positionofreplacedchar, stringtoreplaceitwith)
    unsigned int pos = 0;
    tokens.clear();
    string toTokenize = inFix,
           token,
           fromChar("A");
    if (toTokenize.find_first_of("-") < toTokenize.size())
    {
        while ((pos = toTokenize.find("-", pos + 2)) < toTokenize.size())
            toTokenize.replace(pos,2,"+-");
    }
    cout << toTokenize;
    while(!toTokenize.empty())
    {
        trim(toTokenize);
        fromChar[0] = toTokenize[0];
        if(fromChar == "+")
        {
            trim(fromChar);
            tokens.push_back(fromChar);
            toTokenize.erase(0,1);
        }

        else
        {
            pos = toTokenize.find_first_of("+");
            token = toTokenize.substr(0,pos);
            toTokenize =  pos > toTokenize.size() ? "" : toTokenize.substr(pos);
            cout << "Tokenize: " << toTokenize << endl;
            cout << "Token: " << token << endl;
            tokens.push_back(token);
        }
    }

}

void expression::trim(string &item)
{
    while(item[0] == ' ')
        item.erase(0,1);
    while(item[item.size()-1] == ' ')
        item.erase(item.size()-1);
}


expression& expression::operator<<(const string &input)
{
    inFix = input;
    postFix.clear();
    tokens.clear();
    tokenize();
    return *this;
}

//bool goodExpression()
//{
//    //used to check if their input makes sense
//}

//fraction evaluateAt(const fraction &value)
//{
//    //used for evaluate e.g. F(1/4) =
//}

//ostream& operator<<(ostream &out, const expression &exp)
//{

//}

//istream& operator>>(istream &in, expression &exp)
//{

//}


expression& expression::derivative(unsigned int x)
{
    for(unsigned int i = 0; i < terms.size(); ++i)
        for(unsigned int j = 1; j <= x; ++j)
        {
            terms[i].coef = terms[i].coef * terms[i].power;
            terms[i].power = terms[i].power - 1;
        }
    return *this;
}


void expression::Destroy()
{
    for(unsigned int i = 0; i < terms.size(); ++i)
        terms.erase(terms.begin());
}
