#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#define TAPESIZE 256
#define TABLESIZE 256

char tape[TAPESIZE];
char actionTable[TABLESIZE][5];
int actualTableSize = 0;
int pointer = 0;
char state;

void init(const char*);
void debug();

int main(int argc, const char * argv[])
{
    if (argc != 2)
    {
        printf("Correct usage: %s filename\n", argv[0]);
        exit(0);
    }
    
    init(argv[1]);
    debug();
    
    while (1)
    {
        for (int i = 0; i < actualTableSize; i++)
        {
            if (actionTable[i][0] == state && actionTable[i][1] == tape[pointer])
            {
                state = actionTable[i][2];
                tape[pointer] = actionTable[i][3];
                switch (actionTable[i][4])
                {
                    case 'R':
                        pointer++;
                        break;
                    case 'L':
                        pointer--;
                        break;
                    case 'H':
                        debug();
                        exit(0);
                }
            }
        }
    }
}

void init(const char* filename)
{
    ifstream fin;
    fin.open(filename);
    if (!fin)
    {
        printf("Error opening %s\n", filename);
        exit(1);
    }
    
    // Read in initial state
    fin >> state;
    fin.ignore(256, '\n');
    
    // Read in initial values for tape
    char temp;
    for (int i = 0; ; i++)
    {
        fin >> temp;
        if (temp == '/') break;
        tape[i] = temp;
    }
    fin.ignore(256, '\n');
    
    // Read in action table
    for (int i = 0; ; i++)
    {
        fin >> temp;
        if (temp == '-') break;
        actualTableSize++;
        actionTable[i][0] = temp;
        fin >> actionTable[i][1];
        fin >> actionTable[i][2];
        fin >> actionTable[i][3];
        fin >> actionTable[i][4];
        fin.ignore(256, '\n');
    }
    fin.ignore(256, '\n');
    fin >> pointer;
    pointer--;
}

void debug()
{
    //cout << state << endl;
    
    for (int i = 0; i < strlen(tape); i++)
    {
        cout << tape[i];
    }
    cout << endl;
    
    /*
    for (int i = 0; i < actualTableSize; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%c",actionTable[i][j]);
        }
        cout << endl;
    }
    cout << pointer << endl;*/
}
