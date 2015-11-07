#include "NaiveBayes.h"
#include <sstream>
using namespace std;

NaiveBayes::NaiveBayes(string learn, string classify, string output, int rows, int columns, int uniqueVals)
{
    FILENAME_INPUT_LEARN = learn;
    FILENAME_INPUT_CLASSIFY = classify;
    FILENAME_OUTPUT = output;
    MAX_ROWS = rows+1;
    MAX_COLUMNS = columns+1;
    MAX_UNIQUE_VALUES = uniqueVals+1;
    
    // Initialization of all the arrays
	D = new string*[MAX_ROWS];
	A = new struct UniqueValues*[MAX_ROWS];
	C = new int**[MAX_ROWS];
	P = new float**[MAX_ROWS];
	U = new string[MAX_ROWS];
	for (int i = 0; i < MAX_ROWS; i++)
    {
		D[i] = new string[MAX_COLUMNS];
		A[i] = new struct UniqueValues[MAX_COLUMNS];
		C[i] = new int*[MAX_COLUMNS];
		P[i] = new float*[MAX_COLUMNS];
		for (int j = 0; j < MAX_COLUMNS; j++)
        {
			C[i][j] = new int[MAX_UNIQUE_VALUES];
			P[i][j] = new float[MAX_UNIQUE_VALUES];
        }
    }
}

void NaiveBayes::Preprocessor()
{
    int i, j, k;
    for (i = 1; i < MAX_ROWS; i++)
    {
        for (j = 1; j < MAX_COLUMNS; j++)
        {
            D[i][j] = "";
            A[i][j].value = "";
            A[i][j].count = 0;
            for (k = 1; k < MAX_UNIQUE_VALUES; k++)
            {
                C[i][j][k] = 0;
                P[i][j][k] = 0.0f;
            }
        }
    }
    i = 1;
    j = 1;
    
    ifstream fin;
    fin.open(FILENAME_INPUT_LEARN.c_str());
    if (!fin)
    {
        printf("Error opening %s\n", FILENAME_INPUT_LEARN.c_str());
        exit(1);
    }
    
    // Following code adapted from
    // https://www.daniweb.com/programming/software-development/threads/53349/getline-with-multiple-delimiters
    // Used to read from file with multiple delimiters.
    string x;
    stringstream iss;
    getline(fin, x); // Get rid of the headers
    while (getline(fin, x))
    {
        iss << x;
        string token;
        while (getline(iss, token, ','))
        {
            BuildTables(token, i, j);
            j++;
        }
        
        columnsInTable = j - 1;
        i++;
        j = 1;
        
        iss.clear();
        if (fin.eof()) break;
    }
    instancesInTable = i - 1;
    fin.close();
    /*// For debugging purposes only.
    for (int a = 1; a < MAX_ROWS; a++)
    {
        for (int b = 1; b < MAX_COLUMNS; b++)
        {
            printf("%10s", D[a][b].c_str());
        }
        printf("\n");
    }
    // For debugging purposes only.
    for (int a = 1; a < MAX_ROWS; a++)
    {
        for (int b = 1; b < MAX_COLUMNS; b++)
        {
            printf("A[%i][%i]: v:%s, c:%i\n", a, b, A[a][b].value.c_str(), A[a][b].count);
        }
    }*/
}

void NaiveBayes::Learner()
{
    for (int m = 1; m < instancesInTable; m++)
    {
        int i = XRefD(m, columnsInTable);
        for (int j = 1; j < columnsInTable - 1; j++)
        {
            int k = XRefD(m, j);
            C[i][j][k]++;
        }
    }
    //printf("columnsInTable: %i, UniqueValues: %i\n", columnsInTable, UniqueValues(columnsInTable));
    for (int i = 1; i < UniqueValues(columnsInTable) + 1; i++)
    {
        P[i][columnsInTable][1] = (float)A[i][columnsInTable].count / (float)instancesInTable;
		//printf("P[%i][%i][%i]: %f\n", i, columnsInTable, 1, P[i][columnsInTable][1]);
        for (int j = 1; j < columnsInTable - 1; j++)
        {
            for (int k = 1; k < UniqueValues(j) + 1; k++)
            {
				//printf("C[%i][%i][%i]: %i\n", i, j, k, C[i][j][k]);
				//printf("A[%i][%i]: %i\n", i, columnsInTable, A[i][columnsInTable].count);
                P[i][j][k] = (float)C[i][j][k] / (float)A[i][columnsInTable].count;
				//printf("P[%i][%i][%i]: %f\n", i, j, k, P[i][j][k]);
            }
        }
    }
}

void NaiveBayes::Classify()
{
    ifstream fin;
    fin.open(FILENAME_INPUT_CLASSIFY.c_str());
    if (!fin)
    {
        printf("Error opening %s\n", FILENAME_INPUT_CLASSIFY.c_str());
        exit(1);
    }
    
    ofstream fout;
    fout.open(FILENAME_OUTPUT.c_str());
    if (!fout)
    {
        printf("Error opening %s\n", FILENAME_OUTPUT.c_str());
        exit(1);
    }
    
    // Following code adapted from
    // https://www.daniweb.com/programming/software-development/threads/53349/getline-with-multiple-delimiters
    // Used to read from file with multiple delimiters.
    string x;
    stringstream iss;
    
    while (getline(fin, x))
    {
        iss << x;
        string token, c;
        int i = 1;
        while (getline(iss, token, ','))
        {
            U[i++] = token;
            fout << token << ",";
        }
        
        c = Classifier();
        fout << c << endl;
        //printf("Person %i: %s\n", person++, c.c_str());
        
        iss.clear();
        if (fin.eof()) break;
    }
    fin.close();
    fout.close();
}

string NaiveBayes::Classifier()
{
    float p = 0.0f;
    float pTemp = 0.0f;
    string c;
	for (int i = 1; i < UniqueValues(columnsInTable) + 1; i++)
    {
		pTemp = P[i][columnsInTable][1];
		for (int j = 1; j < columnsInTable - 1; j++)
        {
            int k = XRefU(j);
            pTemp = pTemp * P[i][j][k];
        }
        if (pTemp > p)
        {
            p = pTemp;
			c = A[i][columnsInTable].value;
        }
    }
    return c;
}

void NaiveBayes::BuildTables(string x, int i, int j)
{
    D[i][j] = x;
    int k = 1;
    while (A[k][j].value != "")
    {
        if (x == A[k][j].value)
            break;
        k++;
    }
    A[k][j].value = x;
    A[k][j].count++;
}

int NaiveBayes::UniqueValues(int j)
{
    int k = 0;
    while (A[k + 1][j].value != "")
        k++;
    return k;
}

int NaiveBayes::XRefD(int m, int j)
{
    for (int i = 1; i < UniqueValues(j) + 1; i++)
    {
        if (D[m][j] == A[i][j].value)
        {
            return i;
        }
    }
    return 0;  // Not sure about this
}

int NaiveBayes::XRefU(int j)
{
    for (int i = 1; i < UniqueValues(j) + 1; i++)
    {
        if (U[j] == A[i][j].value)
        {
            return i;
        }
    }
    return 0; // Not sure about this
}