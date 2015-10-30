#ifndef __substring_cpp
#define __substring_cpp

#include "substring.h"


substring::substring() //constructor
{
	x = "";
	y = "";
}

void substring::readSubString() //read in the subsequence to two strings, convert those strings into the x and y arrays
{
	ifstream inFile;
	inFile.open("substring.txt");
	if (!inFile)
	{
		cout << "InFile did not open" << endl;
	}

	string tempX, tempY;

	getline(inFile, tempX);
	getline(inFile, tempY);

	parseStrings(tempX, tempY, x, y); //build the strings
	//cout << tempX << endl; //debug statements
	//cout << tempY << endl;
	cout << x << endl;
	cout << y << endl;
}

void substring::parseStrings(string tempX, string tempY, string &x, string &y) //removing the brackets and commas from subsequence and converting to arrays
{
	for (unsigned i = 0 ; i < tempX.length(); i++) //parse out tempX and save in x
	{
		if (tempX[i] == '<' || tempX[i] == '>' || tempX[i] == ',' || tempX[i] == ' ')
			continue;
		else
			x += tempX[i]; //add the temp character to x
	}

	for (unsigned i = 0; i < tempY.length(); i++) //parse out tempY and save in y
	{
		if (tempY[i] == '<' || tempY[i] == '>' || tempY[i] == ',' || tempY[i] == ' ')
			continue;
		else
			y += tempY[i]; //add the temp character to y;
	}
}


void substring::longestCommonSubsequence(string x, string y)
{
	int m = x.length();
	int n = y.length();
	int q=0, r=0;

	int** c = new int*[m]; //dynamic init a 2d array for c and then b
	for (int i = 0; i < m; i++)
		c[i] = new int[n];

	char** b = new char*[m];
	for (int i = 0; i < m; i++)
		b[i] = new char[n];

	//algorithm starts
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			c[i][j] = 0;
			b[i][j] = ' ';
		}
	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (x[i] == y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = '\\';
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = '|';
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = '-';
			}
			q = i;
			r = j;
			cout << b[i][j];
		}
		cout << endl;
		
	}
	traverse(q, r, x, b);

}

void substring::traverse(int i, int j, string x, char** b) //traverse b and print out the lcs
{

	if (i == 0 || j == 0)
		return;
	if (b[i][j] == '\\')
	{
		traverse(i - 1, j - 1, x, b);
		print(x[i]); //print the lcs
	}
	else if (b[i][j] == '|')
		traverse(i - 1, j, x, b);
	else
		traverse(i, j - 1, x, b);
	return;
};


void substring::print(char x)
{
	cout << x; //prints x
}


void substring::executeLCS()
{
	longestCommonSubsequence(x, y); //call lcs for main
}

void substring::deleteShit(int** c)
{
	delete[] c; //delete the dynamic array
}

#endif