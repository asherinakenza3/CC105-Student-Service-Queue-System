#include "Input.h"
#include <iostream>
#include <limits>
using namespace std;
int number(const string& prompt,int low,int high)
{
    int x;
    while(true)
    {
        cout<<prompt;
        if(cin>>x && x>=low && x<=high)
        {
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            return x;
        }
        cout<<"Invalid entry. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
}
string line(const string& p)
{
    string s;
    do
    {
        cout<<p;
        getline(cin,s);
        if(s.find_first_not_of(" \t\r\n")==string::npos)cout<<"Cannot be blank.\n";
    }
    while(s.find_first_not_of(" \t\r\n")==string::npos);
    return s;
}
