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
    inFix = input;
    postFix.clear();
    tokens.clear();
    tokenize();
    vectorizetokens();
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
    for (unsigned int i = 0; i < terms.size(); ++i)
        cout << "coeff:" << terms[i].coef << endl
             << "power: " <<terms[i].power << endl;
   cout << "end of terms." << endl
        << "this code block located on line " << __LINE__ << " of expression.cpp" << endl;
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

Term::Term(void) {}

void Term::init(const string &strTerm)
{
        e = strTerm;
        int i = 0; int j = 0; int k = 0;

        for (i=0; i<strTerm.length(); i++){
            if (Character::isDigit(strTerm[i])) {
                continue;
            } else {
                break;
            }
        }
        c = strTerm.substr(0,i);
        if (i==strTerm.length()) {
            return;
        }

        for (j=i;j<strTerm.length();j++){
            if (Character::isCharacter(strTerm[j])) {
                continue;
            } else {
                break;
            }
        }
        v = strTerm.substr(i,j);
        if (j==strTerm.length()) {
            return;
        }
        if (!Character::isPower(strTerm[j]) )
          return;
        j++;
        for(k=j;k<strTerm.length();k++){
          if (Character::isDigit(strTerm[k]))
              continue;
          else
            break;
        }
        p = strTerm.substr(j,k);
    }

    float Term::evaluate(string val = "") {
        float _v = 1.0;
        float _p = 1.0;
        float _c = 1.0;
        if (c.length() > 0) {
            _c = stof(this->c);
        }
        if ( (val.length() > 0) && (v.length() > 0)) {
            _v = stof(val);
        }
        if (this->p.length() > 0) {
            _p = stof(p);
        }

        return (_c) * pow(_v,_p);
    }

    Expression::Expression(void) {}

    void Expression::init(string expr){
        e = expr;
    }

    int Expression::priority(string oprtr){
        if ((oprtr == " + ") || (oprtr == " - ")) {
            return 1;
        }
        if ((oprtr == " * ") || (oprtr == " / ")) {
            return 2;
        }
    }

    bool Expression::isOperator(string oprtr){
        if ((oprtr == " + ") || (oprtr == " - ") || (oprtr == " * ") || (oprtr == " / ")) {
            return true;
        }
        return false;
    }

    float Expression::compute(string oprtr, string lOprnd, string rOprnd, string vValue = ""){
        Term lTerm;
        Term rTerm;
        lTerm.init(lOprnd);
        rTerm.init(rOprnd);
        if (oprtr == " + ") {
            return lTerm.evaluate(vValue) + rTerm.evaluate(vValue);
        }
        if (oprtr == " - ") {
            return lTerm.evaluate(vValue) - rTerm.evaluate(vValue);
        }
        if (oprtr == " * ") {
            return lTerm.evaluate(vValue) * rTerm.evaluate(vValue);
        }
        if (oprtr == " / ") {
            return lTerm.evaluate(vValue) / rTerm.evaluate(vValue);
        }
        return 0;
    }

    string Expression::evaluate(string vValue){
      stack<string> eStack;

      for(int i=0; i<postfix.size(); i++){
        if (isOperator(postfix.c[i])){
          string b = eStack.top();
          eStack.pop();
          string a = eStack.top();
          eStack.pop();
          eStack.push(to_string(compute(postfix.c[i], a, b, vValue )));
        } else {
          eStack.push(postfix.c[i]);
        }
      }//end of for

      string retVal = eStack.top();
      eStack.pop();
      return retVal;
    }

    void Expression::infixToPostfix()
    {
      string t = "";  //current token
      estack oStack; //temp operator stack

      for (int i=0; i<e.length(); i++) {
        t += e[i];

        if (t.length() < 3) {
          continue;
        }

        string oprtr = t.substr(t.length()-3,t.length());
        string operand = t.substr(0,t.length()-3);

        if (!isOperator(oprtr)){
          continue;
        }

        int ps = 1;
        int poStack = 1;

        postfix.push(operand);

        while(!oStack.empty()){
          //Till the time stack's top operator greater than equal to infixStr operator than add to postfixStr else break
          if(priority(oStack.top()) >= priority(oprtr)){
            postfix.push(oStack.top());
            oStack.pop();
          } else {
            break;
          }
        }//end of while
        //push the current infixStr operator to stack
        oStack.push(oprtr);
        //this.postfix.push(operand);
        t = "";
      }//end of for

      postfix.push(t);
      while(!oStack.empty()){
        postfix.push(oStack.top());
        oStack.pop();
      }//end of while
    }
