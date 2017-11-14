#include "fraction.h"
#include "expression.h"
#include <string>
#include <iomanip>
#include <map>
#include <iostream>
#include <fstream>

using namespace std;

//make a map to save expressions as a certain variable

//make an expression exists function: for if they try to print out "print b"

//function for checking if they input "LET EVALUATE..."
//make a for loop that checks if a string is equal to their input, and
//increment an integer as you go along
//once it finds the correct statement, use that integer in a switch statement

//in order to have only one input
//need a function that takes in "istream" so whether it takes in cin or a filestream, it does
//certain things

void openInput(const string &name, ifstream &in);
void openOutput(const string &name, ofstream &out);
void CommandLine(const char *title, int argc, char *argv[], ifstream &inFile, string &inName);
//void commmandLet(string input, string &index, string &expression, bool &valid);
//void commmandEval(string input, string &index, bool &valid);
//void commmandPrint(string input, string &index, bool &valid, map<char, expression> store);
//void trim(string &item);


int main(int argc, char *argv[])
{

    bool again;
    string input, number, command, index, exp, inName;
    Expression e;
    ifstream inFile;
    map<char, expression> map;

    cout << "INPUT: ";
    getline(cin,input);
    e.init(input);
    e.infixToPostfix();
    cout << "\nWhere do you want to evaluate it?: ";
    cin >> number;
    //string ans = ;
    cout << e.evaluate(number);
//    do
//    {
//        cout<<"INPUT: ";
//        getline(cin, input);
//        again = true;
//        if (input == "")
//        {
//            again = false;
//        }
//        else if (command == "LET")
//        {
//           commmandLet(input, index, exp, again);
//           Polynomial << exp;
//           cout << index << " = " << Polynomial << endl;
//           store[index[0]] = Polynomial;
//       }
//       else if (command == "EVAL")
//       {
//           commmandPrint(input, index, again, store);
//           commmandEval(input, index, again);
//       }
//       else if (command == "PRINT")
//       {
//           commmandPrint(input, index, again, store);
//       }
//       else
//       {
//            cout << "\nInvalid command, please try again";
//            again = true;
//       }
//    }
//    while (again);

    return 0;
}

//void commmandLet(string input, string &index, string &expression, bool &valid)
//{
//    int pos;

//    trim(input);
//    pos = input.find_first_of(' ');
//    index = input.substr(0, pos);
//    input.erase(0,pos);
//    trim(index);
//    index[0] = toupper(index[0]);

//    pos = input.find_first_of('=');
//    expression = input.substr(pos+1, string::npos);
//    trim(expression);
//}

//void commmandPrint(string input, string &index, bool &valid, map<char, expression> store)
//{
//    trim(input);
//    index = input[0];
//    index[0] = toupper(index[0]);
//    cout << index << " = " << store[index[0]] << endl;

//}

//void commmandEval(string input, string &index, bool &valid)
//{
//    fraction x;
//    string temp;
//    trim(input);
//    index = toupper(input[0]);
//    input.erase(0,1);
//    int pos = input.find_first_of('(');
//    int end = input.rfind(')');
//    temp = input.substr(pos+1, end-1);

//    cout<<index<<"("<<temp<<")"<<" = "<<"EVALUATION"<<endl;


//}

void trim(string &item)
{
    unsigned int pos = 0;
    while(item[0] == ' ')
        item.erase(0,1);
    while(item[item.size()-1] == ' ')
        item.erase(item.size()-1);
}

void CommandLine(const char *title, int argc, char *argv[], ifstream &inFile, string &inName)
{
    if (argc == 1)
    {
        if (argv[0][1] == '/h' || argv[0][1] == '/?')
        {
            cout << "In order to properly utilize the command line, you must put in either "
                 << "1 or 2 arguments" << endl << endl
                 << "If you are inputting 1 argument into the command line, it must contain the "
                 << "filename of the file you wish to load into the program." << endl
                 << "This filename must include the extension of the file as well (e.g. .exp)" << endl << endl
                 << "If you are inputting 2 arguments the first of the two must be either EXECUTE or RECORD" << endl
                 << "followed by the second argument being the previously stated filename in correct format" << endl;
            exit(0);
        }
        else
        {
            //inFile = argv[1];
            //openOutput(inFile, out);
        }

    }
    else if (argc == 2)
    {

    }
    else if (argc >= 3)
    {
        cout << "Too many command line arguments, program will now exit.";
        exit(1);
    }

}

void openInput(const string &name, ifstream &in){
    string extension;
    bool again;
    if(name.find(".") > name.size())
    {
        cout<<"Please enter a file extension (press enter for .txt): ";
        getline(cin, extension);
        if(extension.empty())
            extension = ".txt";
    }
    do
    {
        string temp = (name + extension);
        again = false;
        in.open(temp.c_str(), ios::binary);
        if(in.fail())
        {
            again = true;
            cout<<"That file does not exist for input"<<endl
                <<"Please enter another file name: ";
            cin>>temp;
        }
    }while(again);
}


void openOutput(const string &name, ofstream &out){
    string extension, answer, temp;
    ifstream in;
    if(name.find(".") > name.size())
    {
        cout<<"Please enter a file extension (press enter for .txt): ";
        getline(cin, extension);
        if(extension.empty())
            extension = ".txt";
    }
    temp = name + extension;
    in.open(temp.c_str());
    in.close();

    if(!in.fail())
    {
        out.open(temp.c_str(), ios::binary);

    } else
    {
        in.close();
        in.clear();
        out.open(temp.c_str());
    }
}

void mapLoad(map<char, expression> &map){
    map['A'];
    map['B'];
    map['C'];
    map['D'];
    map['E'];
    map['F'];
    map['G'];
    map['H'];
    map['I'];
    map['J'];
    map['K'];
    map['L'];
    map['M'];
    map['N'];
    map['O'];
    map['P'];
    map['Q'];
    map['R'];
    map['S'];
    map['T'];
    map['U'];
    map['V'];
    map['W'];
    map['X'];
    map['Y'];
    map['Z'];
}
