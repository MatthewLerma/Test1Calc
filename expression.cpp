#include "expression.h"
#include <sstream>

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
            cout << "Tokenize: " << toTokenize << endl;
            cout << "Token: " << token << endl;
            tokens.push_back(token);
        }
        else
        {
            token = toTokenize;
            cout << "Tokenize: " << toTokenize << endl;
            cout << "Token: " << token << endl;
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
    int pos = 0;
    fraction co, po;
    stringstream ss;
    inFix = input;
    postFix.clear();
    tokens.clear();
    tokenize();
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
            //still need to add something for non x powers (5x) with no ^

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
    for (unsigned int i = 0; i < terms.size(); ++i)
        cout << terms[i];
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

//Used to set the co-efficient to 1 of variables with none, or only a negative sign
void expression::Nocoeffcheck(string &token)
{
    int pos = token.find("X");
    if (pos == 0)
    {
        token = "1" + token;
    }
    else if (token.substr(0,pos) == "-")  //This part is sketchy, keep an eye on it
    {
        token.replace((pos-1),2,"-1");
    }

}

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
