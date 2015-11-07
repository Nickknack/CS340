#include <stdio.h>
//using namespace std;

#include "NaiveBayes.h"

int main()
{
    NaiveBayes computer("computer-labeled.txt", "computer-unlabeled.txt", "computer-classified.txt", 15, 5, 2);
    NaiveBayes cars("car-labeled.txt", "car-unlabeled.txt", "car-classified.txt", 1729, 7, 4);
    
    computer.Preprocessor();
    computer.Learner();
    computer.Classify();
    //computer.Classifier();
    
    cars.Preprocessor();
    cars.Learner();
    cars.Classify();
    //cars.Classifier();

    return 0;
}