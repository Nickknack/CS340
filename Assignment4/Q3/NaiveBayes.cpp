#include "NaiveBayes.h"
#include <sstream>
using namespace std;

NaiveBayes::NaiveBayes(string input, string output, int rows, int columns, int uniqueVals)
{
    FILENAME_INPUT = input;
    FILENAME_OUTPUT = output;
    MAX_ROWS = rows;
    MAX_COLUMNS = columns;
    MAX_UNIQUE_VALUES = uniqueVals;
    
    // Initialization of all the arrays
    D = new string*[rows];
    A = new struct UniqueValues*[rows];
    C = new int**[rows];
    P = new float**[rows];
    U = new string[rows];
    for (int i = 0; i < rows; i++)
    {
        D[i] = new string[columns];
        A[i] = new struct UniqueValues[columns];
        C[i] = new int*[columns];
        P[i] = new float*[columns];
        for (int j = 0; j < columns; j++)
        {
            C[i][j] = new int[uniqueVals];
            P[i][j] = new float[uniqueVals];
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
            for (k = 1; k > MAX_UNIQUE_VALUES; k++)
            {
                C[i][j][k] = 0;
                P[i][j][k] = 0.0;
            }
        }
    }
    i = 1;
    j = 1;
    
    ifstream fin;
    fin.open(FILENAME_INPUT.c_str());
    if (!fin)
    {
        printf("Error opening %s\n", FILENAME_INPUT.c_str());
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
        string token;
        while (getline(iss, token, ','))
        {
            BuildTables(token, i, j);
            j++;
        }
        
        columnsInTable = j;
        i++;
        j = 1;
        
        iss.clear();
        if (fin.eof()) break;
    }
    instancesInTable = i - 1;
    
    for (int a = 1; a < MAX_ROWS; a++)
    {
        for (int b = 1; b < MAX_COLUMNS; b++)
        {
            printf("%10s", D[a][b].c_str());
        }
        printf("\n");
    }
    for (int a = 1; a < MAX_ROWS; a++)
    {
        for (int b = 1; b < MAX_COLUMNS; b++)
        {
            printf("A[%i][%i]: v:%s, c:%i\n", a, b, A[a][b].value.c_str(), A[a][b].count);
        }
    }
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
    for (int i = 1; i < UniqueValues(columnsInTable); i++)
    {
        P[i][columnsInTable][1] = A[i][columnsInTable].count / instancesInTable;
        for (int j = 1; j < columnsInTable - 1; j++)
        {
            for (int k = 1; k < UniqueValues(j); k++)
            {
                P[i][j][k] = C[i][j][k] / A[i][columnsInTable].count;
            }
        }
    }
    for (int a = 0; a < MAX_ROWS; a++)
    {
        for (int b = 0; b < MAX_COLUMNS; b++)
        {
            for (int c = 0; c < MAX_UNIQUE_VALUES; c++)
            {
                printf("C[%i][%i][%i]: %i\n", a, b, c, C[a][b][c]);
                printf("P[%i][%i][%i]: %f\n", a, b, c, P[a][b][c]);
            }
        }
    }
}

string NaiveBayes::Classifier()
{
    int n = columnsInTable;
    float p = 0.0;
    string c;
    for (int i = 1; i < UniqueValues(n); i++)
    {
        float pTemp = P[i][n][1];
        for (int j = 1; j < n - 1; j++)
        {
            int k = XRefU(j);
            pTemp = pTemp * P[i][j][k];
        }
        if (pTemp > p)
        {
            p = pTemp;
            c = A[i][n].value;
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
    for (int i = 1; i < UniqueValues(j); i++)
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
    for (int i = 1; i < UniqueValues(j); i++)
    {
        if (U[j] == A[i][j].value)
        {
            return i;
        }
    }
    return 0; // Not sure about this
}