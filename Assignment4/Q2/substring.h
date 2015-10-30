#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class substring
{
private:
	string x, y; //final result holding the longest common subsequence


public:
	substring(); //constructor
	void readSubString(); //take in the strings from file
	void parseStrings(string, string, string &, string &); //parse out the commas and brackets
	void longestCommonSubsequence(string, string);
	void traverse(int, int, string, char**);
	void print(char);
	void executeLCS();
	void deleteShit(int**);
};