#include <stdio.h>

#include "NaiveBayes.h"

int main()
{
    NaiveBayes computer("computer-labeled.txt", "computer-unlabeled.txt", "computer-classified.txt", 15, 5, 2);
    NaiveBayes cars("car-labeled.txt", "car-unlabeled.txt", "car-classified.txt", 1729, 7, 4);
    
    // Preprocesses the labelled data set
    computer.Preprocessor();
    // Learns from the labelled data set
    computer.Learner();
    // Reads the unlabelled data set, and classifies each
    computer.Classify();
    
    // Preprocesses the labelled data set
    cars.Preprocessor();
    // Learns from the labelled data set
    cars.Learner();
    // Reads the unlabelled data set, and classifies each
    cars.Classify();

    return 0;
}