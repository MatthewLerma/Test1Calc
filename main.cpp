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
void openOutput(const char *title, const string &name, ofstream &out);
void CommandLine(int argc, char *argv[], ifstream &inFile, string &inName, ofstream &outFile, string &outName);
void initializeMap(map<char, expression> &map);
void loadMap(ifstream &in, map<char, expression> &themap);
void saveMap(ofstream &out, map<char, expression> &themap);
string getCommand(string &input);
string getFileName(string title);

//void commmandLet(string input, string &index, string &expression, bool &valid);
//void commmandEval(string input, string &index, bool &valid);
//void commmandPrint(string input, string &index, bool &valid, map<char, expression> store);
void trim(string &item);

int main(int argc, char *argv[])
{

    bool again;
    string input, number, command, index, exp, inName, outName;
    Expression e;
    ifstream inFile;
    ofstream outFile;
    map<char, expression> map;
    initializeMap(map);
    loadMap(inFile, map);


    CommandLine(argc, argv, inFile, inName, outFile, outName);

//    cout << "INPUT: ";
//    getline(cin,input);
//    e.init(input);
//    e.infixToPostfix();
//    cout << "\nWhere do you want to evaluate it?: ";
//    cin >> number;
//    //string ans = ;
//    cout << e.evaluate(number);


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

void trim(string &item)
{
    while(item[0] == ' ')
        item.erase(0,1);
    while(item[item.size()-1] == ' ')
        item.erase(item.size()-1);
}

string getFileName(string title)
{
    string name;
    cout<<title;
    cin>>name;
    cin.clear();
    cin.ignore(255, '\n');
    return name;
}

string getCommand(string &input)
{
    string instruction;
    int pos = input.find_first_of(' ');
    instruction = input.substr(0,pos);
    input.erase(0,pos);
    trim(instruction);
    for (int i = 0; i < instruction.size(); i++)
        instruction[i] = toupper(instruction[i]);
    return instruction;
}

void loadMap(ifstream &in, map<char, expression> &themap)
{
    string temp, name, index;
    int pos;
    expression x;
    name = getFileName("Please enter input file name: ");
    openInput(name,in);
    map<char,expression>::iterator i;

    for(i= themap.begin(); i != themap.end(); ++i)
    {
        getline(in,temp);
        index = getCommand(temp);
        pos = temp.find_first_of('=');
        temp.substr(pos+1, string::npos);
        while(temp[0] == ' ' || temp[0] == '=')
            temp.erase(0,1);
        x<<temp;
        themap[i->first] = x;
        cout<<i->first<<" = "<<x<<endl;
        x.clear();
    }
}

void saveMap(ofstream &out, map<char, expression> &themap)
{
    string name;
    name = getFileName("Please enter an output file name: ");
    openOutput(".exp" ,name, out);
    for (map<char,expression>::iterator i=themap.begin(); i!=themap.end(); ++i){
        out<<i->first<<" = "<<i->second<<endl;
    }

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


void CommandLine(int argc, char *argv[], ifstream &inFile, string &inName, ofstream &outFile, string &outName)
{
    string temp;
    if (argc == 1)
    {
        return;
    }
    else if (argc == 2)
    {
        if (argv[1][0] == '/')
        {
            if (argv[1][1] == 'h' || argv[1][1] == '?')
            {
                cout << "In order to properly utilize the command line, you must put in either " << endl
                     << "1 or 2 arguments" << endl << endl
                     << "If you are inputting 1 argument into the command line, it must contain the " << endl
                     << "filename of the file you wish to load into the program." << endl
                     << "This filename must include the extension of the file as well (e.g. .exp)" << endl << endl
                     << "If you are inputting 2 arguments the first of the two must be either EXECUTE or RECORD" << endl
                     << "followed by the second argument being the previously stated filename in correct format" << endl;
                exit(0);
            }
            else
            {
                cout << "Invalid command line parameter\n";
                exit(1);
            }
        }
        else
        {
            outName = argv[1];
            openOutput(".exp",outName, outFile);
        }

    }
    else if (argc == 3)
    {
        temp = argv[1];
        for (int i = 0; i < temp.size(); ++i)
        {
            toupper(temp[i]);
        }
        if (temp == "EXECUTE")
        {
            outName = argv[2];
            cout << outName;
            cout << "Execute successfully read" << endl;
        }
        else if (temp == "RECORD")
        {
            inName = argv[2];
            cout << inName;
            cout << "Record successfully read" << endl;
        }
        else
        {
            cout << "Invalid first parameter";
            exit(1);
        }
    }
    else if (argc >= 4)
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
        cout<<"Please enter a file extension (press enter for .spt): ";
        getline(cin, extension);
        if(extension.empty())
            extension = ".spt";
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
                <<"Please enter another file name with extension: ";
            cin>>temp;
        }
    }while(again);
}

void openOutput(const char *title, const string &name, ofstream &out){
    string extension, answer, temp;
    char c;
    ifstream in;
    if(name.find(".") > name.size())
    {
        cout<<"Please enter a file extension (press enter for .exp): ";
        getline(cin, extension);
        if(extension.empty())
            extension = title;
    }
    temp = name + extension;
    in.open(temp.c_str());

    if(!in.fail())
    {
        in.clear();
        cout << "File already exists, (O)verwrite, or (E)xit?: ";
        cin >> answer;
        c = toupper(answer[0]);
        if (c == 'O')
        {
            out.open(temp.c_str(), ios::binary);
        }
        else
        {
            cout << "File already exists\n";
            exit(0);
        }

    } else
    {
        in.close();
        in.clear();
        out.open(temp.c_str());
    }
}

void initializeMap(map<char, expression> &map)
{
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
