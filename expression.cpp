#include "expression.h"
#include <sstream>



expression::expression()
{

}

expression::expression(string &ExpStore)
{
    maketerms(ExpStore);

}
//void expression::loadMaps()
//{
//    precedence["+"] = precedence["-"] = 1;
//}

void expression::clear()
{
    terms.clear();
}

expression::expression(const expression &other)
{
    copy(other);
}

expression::~expression()
{
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
    terms.clear();
    for (unsigned int i = 0; i < other.terms.size();++i)
    {
        terms.push_back(other.terms[i]);
    }
    ExpressionStore = other.ExpressionStore;
}

void expression::tokenize()
{
    size_t pos = 0;
    tokens.clear();
    string toTokenize = ExpressionStore,
           token,
           fromChar("A");
    if (toTokenize.find_first_of("-") < toTokenize.size())
    {
        while ((pos = toTokenize.find("-", pos + 2)) < toTokenize.size())
        {
            toTokenize.erase(pos,1);
            toTokenize.insert(pos,"+-");
        }
    }
    while(!toTokenize.empty())
    {
        trim(toTokenize);
        for (unsigned int i = 0; i < toTokenize.size(); ++i)
        {
            toTokenize[i] = toupper(toTokenize[i]);
        }
        fromChar[0] = toTokenize[0];
        if(fromChar == "+")
        {
            trim(fromChar);
            tokens.push_back(fromChar);
            toTokenize.erase(0,1);
        }
        else if ((toTokenize.find_first_of("+")) < toTokenize.size())
        {
            pos = toTokenize.find_first_of("+");
            token = toTokenize.substr(0,pos);
            toTokenize =  pos > toTokenize.size() ? "" : toTokenize.substr(pos);
            tokens.push_back(token);
        }
        else
        {
            token = toTokenize;
            tokens.push_back(token);
            toTokenize.clear();
        }
    }

}

void expression::trim(string &item)
{
    int pos = 0;
    while(item[0] == ' ')
        item.erase(0,1);
    while(item[item.size()-1] == ' ')
        item.erase(item.size()-1);
    while((pos = item.find_first_of(" ")) < item.size())
        item.erase(pos,1);
}


expression& expression::operator<<(const string &input)
{
    maketerms(input);
    return *this;
}

void expression::vectorizetokens()
{
    int pos = 0;
    fraction co, po;
    stringstream ss;
    for (unsigned int i = 0; i < tokens.size(); ++i)
    {
        if (tokens[i] == "+")
        {
            tokens.erase(tokens.begin()+(i));
        }
    }

    for (unsigned int i = 0; i < tokens.size(); ++i)
    {
        if ((pos = tokens[i].find("X", pos)) < tokens[i].size())
        {
            Nocoeffcheck(tokens[i]);
            if((pos = tokens[i].find("^")) < tokens[i].size())
            {
                ss << tokens[i].substr(0,pos);
                ss >> co;
                ss.str("");
                ss.clear();
                ss << tokens[i].substr(pos+1);
                ss >> po;
                ss.str("");
                ss.clear();
                pos = 0;
                terms.push_back(term(co,po));
            }
            else
            {
                pos = tokens[i].find("X", pos);
                ss << tokens[i].substr(0,pos);
                ss >> co;
                ss.str("");
                ss.clear();
                po = 1;
                pos = 0;
                terms.push_back(term(co,po));
            }

        }
        else if ((pos = tokens[i].find("X", pos)) > tokens[i].size())
        {
            ss << tokens[i];
            ss >> co;
            ss.str("");
            ss.clear();
            po = 0;
            pos = 0;
            terms.push_back(term(co,po));
        }
    }
}



ostream& operator<<(ostream &out, expression &exp)
{
    for(int i = 0; i < exp.terms.size(); ++i)
    {
        if ((exp.terms[i].coef) != 0)
        {
            out<<exp.terms[i].coef;
            if((exp.terms[i].power) > 1)
            {
                out<< "X^";
                out<<exp.terms[i].power;
            }
            else if((exp.terms[i].power) == 1)
                out << "X";
            if ((i + 1) < exp.terms.size())
            {
                if (!(exp.Negativecheck(exp.terms[i + 1].coef)))
                {
                    out << "+";
                }
            }
        }
    }
    return out;
}


istream& operator>>(istream &in, expression &exp) //puts everything into a string
{
    return getline(in,exp.ExpressionStore);
}

fraction operator^(expression &expres, fraction &evalnum)
{
    fraction result;
    for (unsigned int i = 0; i < expres.terms.size();++i)
    {
        result += ((expres.terms[i].coef)*(evalnum^(expres.terms[i].power)));
    }
    return result;
}



//Used to set the co-efficient to 1 of variables with none, or only a negative sign
void expression::Nocoeffcheck(string &token)
{
    size_t pos = token.find("X");
    if (pos == 0)
    {
        token = "1" + token;
    }
    else if (token.substr(0,pos) == "-")
    {
        token.replace((pos-1),2,"-1");
    }

}

expression operator % (expression &a, unsigned int x)
{
    expression b = a;
    for(unsigned int i = 0; i < b.terms.size(); ++i)
        for(unsigned int j = 1; j <= x; ++j)
        {
            b.terms[i].coef = b.terms[i].coef * b.terms[i].power;
            b.terms[i].power = b.terms[i].power - 1;
        }
    return b;
}


void expression::Destroy()
{
    for(unsigned int i = 0; i < terms.size(); ++i)
        terms.erase(terms.begin());
}


//Expression math


void expression::consolidateExpression()
{
    for (unsigned int i = 0; i < terms.size(); ++i)
    {
        for(unsigned int k = (i + 1); k < terms.size(); ++k)
        {
            if(terms[i].power == terms[k].power)
            {
                terms[i].coef += terms[k].coef;
                terms[k].coef = 0;
                terms[k].power = 0;
            }
        }
    }
}



void expression::maketerms(const string &input)
{
    ExpressionStore = input;
    tokens.clear();
    tokenize();
    vectorizetokens();
}


expression operator+(expression &a, expression &b)
{
    expression c = a;
    for (unsigned int i = 0; i < b.terms.size(); ++i)
    {
        c.terms.push_back(b.terms[i]);
    }
    c.consolidateExpression();
    return c;
}

expression operator-(expression &a, expression &b)
{
    expression c;
    b.makeNeg();
    c = a+b;
    c.consolidateExpression();
    return c;
}


expression operator*(expression &a, expression &b)
{
    expression c = a;
    for (unsigned int i = 0; i < c.terms.size(); ++i)
    {
        for (unsigned int k = 0; k < b.terms.size(); ++k)
        {
            c.terms[i].coef *= b.terms[i].coef;
            c.terms[i].power += b.terms[i].power;
        }
    }
    c.consolidateExpression();
    return c;
}

void expression::makeNeg()
{

    fraction temp, negative = -1;
    for (unsigned int i = 0; i < terms.size(); ++i)
    {
        temp = terms[i].coef;
        temp *= negative;
        terms[i].coef = temp;
    }
}
bool expression::Negativecheck(fraction &c)
{
    int pos;
    stringstream ss;
    string temp;
    ss << c;
    ss >> temp;
    ss.str("");
    ss.clear();
    if ((pos = temp.find("-")) < temp.size())
    {
        return true;
    }
    else
        return false;
}
