#ifndef NaiveBayes_hpp
#define NaiveBayes_hpp

#include <stdio.h>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

struct UniqueVals
{
    string value;
    int count;
};

class NaiveBayes
{
private:
    string FILENAME_INPUT_LEARN;
    string FILENAME_INPUT_CLASSIFY;
    string FILENAME_OUTPUT;
    int MAX_ROWS;
    int MAX_COLUMNS;
    int MAX_UNIQUE_VALUES;
    
    string** D;
    UniqueVals** A;
    int*** C;
    float*** P;
    string* U;
    int instancesInTable;
    int columnsInTable;
public:
    NaiveBayes(string learn, string classify, string output, int rows, int columns, int uniqueVals);
    void Preprocessor();
    void Learner();
    void Classify();
private:
    string Classifier();
    void BuildTables(string x, int i, int j);
    int UniqueValues(int j);
    int XRefD(int m, int j);
    int XRefU(int j);
};

#endif /* NaiveBayes_hpp */
