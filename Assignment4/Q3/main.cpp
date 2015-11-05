#include <stdio.h>
//using namespace std;

#include "NaiveBayes.h"

int main()
{
    NaiveBayes computer("computer-labeled.txt", "computer-unlabeled.txt", 16, 5, 2);
    NaiveBayes cars("car-labeled.txt", "car-unlabeled.txt", 1000, 7, 3);
    
    computer.Preprocessor();
    computer.Learner();
    computer.Classifier();
    
    cars.Preprocessor();
    cars.Learner();
    cars.Classifier();

    return 0;
}