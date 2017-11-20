#include "fraction.h"
#include "expression.h"
#include <string>
#include <iomanip>
#include <map>
#include <iostream>
#include <fstream>
#include <iterator>

using namespace std;

void openInput(const string &name, ifstream &in);
void openOutput(const char *title, string &name, ofstream &out);
void CommandLine(int argc, char *argv[],string &command, bool &recording, ifstream &inFile, string &inName, ofstream &outFile, string &outName, string &input, string &index, map<char, expression> &themap);
string CommandCheck(string &input);
bool IndexExist(string &index,map<char, expression> &themap);
void HandleCommands(string &command, string &input, string &index,ifstream &inFile, string &inName, ofstream &outFile, string &outName, map<char, expression> &themap);
void LetHandle(string &input, string &index, map<char, expression> &themap);
void PrintHandle(string &input, string &index,map<char, expression> &themap);
fraction EvalHandle(string &input, string &index,map<char, expression> &themap);
void getInput(istream &in, bool recording, ifstream &inFile, string &inName, ofstream &outFile, string &outName, string &input, string &index, map<char, expression> &themap);

void LoadHandle(ifstream &inFile, string &inName, map<char, expression> &themap);
void SaveHandle(ofstream &outFile, string &outName , map<char, expression> &themap);

void ExecuteHandle(string &command, string &input, string &index, ifstream &inFile, string &inName , ofstream &outFile, string &outName, map<char, expression> &themap);
void RecordHandle(ofstream &outFile, string &input);

void trim(string &item);

int main(int argc, char *argv[])
{

    bool again = true, recording = false;
    string input, number, command, index, exp, inName, outName;
    ifstream inFile;
    ofstream outFile;
    map<char, expression> themap;
    expression a,b,c;
    CommandLine(argc, argv,command, recording, inFile, inName, outFile, outName, input, index, themap);

    do
    {
        cout << "INPUT: ";
        getInput(cin,recording, inFile, inName, outFile, outName, input ,index, themap);
    }while(again);
//    map<char,expression>::iterator it;
//    for(it = themap.begin(); it != themap.end(); ++it)
//        cout<<it->first<<" = "<<it->second<<endl;

    return 0;
}

void getInput(istream &in, bool recording, ifstream &inFile, string &inName, ofstream &outFile, string &outName, string &input, string &index, map<char, expression> &themap)
{
    string command;
    if (&in == &cin)
    {
        getline(cin, input);
        if (input == "")
            return;
        if (recording)
        {
            cout << "Input in recording: " << input << endl;
            RecordHandle(outFile,input);
        }
        command = CommandCheck(input);
        HandleCommands(command,input,index, inFile, inName, outFile, outName, themap);
    }
    else
    {
        //file input activated when function called by loading a file
        //getline(inFile,placetoputit) for this, where inFile is from ifstream inFile
//        while (getline(inFile,))

    }
    return;
}

bool IndexExist(string &index,map<char, expression> &themap)
{
    bool exists = false;
    map<char,expression>::iterator it;
    for(it = themap.begin(); it != themap.end(); ++it)
        if(index[0] == (it->first))
        {
            exists = true;
        }
    return exists;
}

string CommandCheck(string &input)
{
    int pos = 0;
    string command;
    for (unsigned int i = 0; i < input.size(); ++i)
    {
        input[i] = toupper(input[i]);
    }
    pos = input.find_first_of(" ");
    command = input.substr(0,pos);
    input.erase(0,pos);
    trim(input);
    return command;
}

void HandleCommands(string &command, string &input, string &index, ifstream &inFile, string &inName, ofstream &outFile, string &outName, map<char, expression> &themap)
{
    if (command == "LET")
    {
        LetHandle(input, index, themap);
    }
    else if (command == "EVAL")
    {
        EvalHandle(input, index, themap);
    }
    else if (command == "PRINT")
    {
        PrintHandle(input, index, themap);
    }
    else if (command == "LOAD")
    {
        inName = input;
        LoadHandle(inFile,inName,themap);
    }
    else if (command == "SAVE")
    {
        outName = input;
        SaveHandle(outFile,outName, themap);
    }
    return;
}

void LetHandle(string &input, string &index,map<char, expression> &themap)
{
    expression temp;
    string indexCheck;
    int pos = 0, derivativecount = 0;
    trim(input);
    pos = input.find_first_of("=");
    index = input.substr(0,pos);
    input.erase(0,pos+1);
    map<char,expression>::iterator it;
    for(it = themap.begin(); it != themap.end(); ++it)
        indexCheck += (it->first);
    if((pos = input.find_first_of(indexCheck)) < input.size())
    {
        if ((pos = input.find_first_of("'")) < input.size())
        {
            do{
                derivativecount ++;
                pos++;
            }while((input.find_first_of("'",(pos))) < input.size());
            pos = input.find_first_of(indexCheck);
            temp = themap[input[pos]] % derivativecount;
        }
        pos = input.find_first_of("+-*'");
        if (input[pos] == '+')
        {
            temp = themap[input[pos - 1]] + themap[input[pos + 1]];
        }
        else if (input[pos] == '-')
        {
            temp = themap[input[pos - 1]] - themap[input[pos +1 ]];
        }
        else if (input[pos] == '*')
        {
            temp = themap[input[pos - 1]] * themap[input[pos +1 ]];
        }
    }
    else
    {
        temp << input; //Loses fraction
    }
    themap[index[0]] = temp;
    cout << index[0] << "=" << themap[index[0]] << endl;

}

void PrintHandle(string &input, string &index,map<char, expression> &themap)
{
    index = input;
    if(IndexExist(index,themap))
    {
        cout << index[0] << "=" << themap[index[0]] << endl;
    }
    else
    {
        cout << "Index does not exist" << endl;
        return;
    }
}

fraction EvalHandle(string &input, string &index,map<char, expression> &themap)
{
    int posOpen = 0, posClose = 0, length;
    fraction evalnum, result;
    expression evalresult, temp;
    index = input[0];
    posOpen = input.find_first_of("(");
    posClose = input.find_first_of(")");
    length = ((posClose - 1) - (posOpen));
    evalnum = fraction(input.substr((posOpen + 1) ,length));
    temp = themap[index[0]];
    result = temp ^ evalnum;
    cout << input << " = "<< result << endl;

    return result;
}

void trim(string &item)
{
    int pos = 0;
    while(item[0] == ' ')
        item.erase(0,1);
    while(item[item.size()-1] == ' ')
        item.erase(item.size()-1);
    while((pos = item.find_first_of(" ")) < item.size())
        item.erase(pos,1);
}

void CommandLine(int argc, char *argv[], string &command,bool &recording, ifstream &inFile, string &inName, ofstream &outFile, string &outName, string &input, string &index, map<char, expression> &themap)
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
            inName = argv[1];
            LoadHandle(inFile,inName, themap);
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
            inName = argv[2];
            ExecuteHandle(command,input, index, inFile, inName, outFile, outName , themap);
        }
        else if (temp == "RECORD")
        {
            cout << "Successfuly Recording" << endl;
            outName = argv[2];
            openOutput(".spt",outName, outFile);
            recording = true;
        }
        else
        {
            cout << "Invalid first parameter" << endl;
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

void openOutput(const char *title, string &name, ofstream &out){
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
    name = temp;
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

void LoadHandle(ifstream &inFile, string &inName ,map<char, expression> &themap)
{
    string temp, index;
    openInput(inName, inFile);
    while(getline(inFile,temp))
    {
        LetHandle(temp,index,themap);
    }
}

void SaveHandle(ofstream &outFile, string &outName ,map<char, expression> &themap)
{
    openOutput(".exp",outName, outFile);
    for (map<char,expression>::iterator i=themap.begin(); i!=themap.end(); ++i)
        outFile<<i->first<<" = "<<i->second<<endl;
}

void ExecuteHandle(string &command, string &input, string &index, ifstream &inFile, string &inName,ofstream &outFile, string &outName ,map<char, expression> &themap)
{
    openInput(inName, inFile);
    while(getline(inFile, input))
    {
        cout << input << endl;
        command = CommandCheck(input);
        HandleCommands(command,input,index, inFile, inName, outFile, outName, themap);
    }
}

void RecordHandle(ofstream &outFile, string &input)
{
    outFile << input << endl;
}
