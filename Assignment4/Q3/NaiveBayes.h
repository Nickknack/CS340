#ifndef NaiveBayes_hpp
#define NaiveBayes_hpp

#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;

struct UniqueValues
{
    string value;
    int count;
};

class NaiveBayes
{
private:
    string FILENAME_INPUT;
    string FILENAME_OUTPUT;
    int MAX_ROWS;
    int MAX_COLUMNS;
    int MAX_UNIQUE_VALUES;
    
    string** D;
    UniqueValues** A;
    int*** C;
    float*** P;
    string* U;
    int instancesInTable;
    int columnsInTable;
public:
    NaiveBayes(string input, string output, int rows, int columns, int uniqueVals);
    void Preprocessor();
    void Learner();
    string Classifier();
private:
    void BuildTables(string x, int i, int j);
    int UniqueValues(int j);
    int XRefD(int m, int j);
    int XRefU(int j);
};

#endif /* NaiveBayes_hpp */
