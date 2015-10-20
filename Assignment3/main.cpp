#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "TaySwiftBinaryTree.h"

struct s {
    char value;
    int count;
};

int main()
{
    ifstream inData;
    string filename;
    cout << "Enter a filename: ";
    cin >> filename;
    
    inData.open(filename.c_str());
    if (!inData)
    {
        cout << "Error reading file" << endl;
        return 1;
    }
    
    TaySwiftBinaryTree searchTree;
    while (!inData.eof())
    {
        char c;
        inData >> c;
        searchTree.Insert(c);
    }
    
    
}
