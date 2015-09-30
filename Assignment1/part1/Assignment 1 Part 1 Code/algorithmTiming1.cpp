#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// This program determines the run time of an algorithm whose life
// is very short. A measurement technique is used that determines
// the number of times the algorithm can run in one second. The
// elapsed time for one run of the algorithm can then be derived
// from this value.

vector<int> prefixAverages1(vector<int>X, int n);
vector<int> prefixAverages2(vector<int>X, int n);
int RandNum() { return rand() % 100; };


int main()
{
	char endRun = 'y';
    
	ofstream data, data2;
	string fileName = "Alg1.csv";
    string fileName2 = "Alg2.csv";
	data.open(fileName.c_str());
    data2.open(fileName2.c_str());
    data << "N,Running Time" << endl;
    data2 << "N,Running Time" << endl;
	
	while (tolower(endRun) != 'n')
	{
        unsigned int n;
        unsigned int reps;
        unsigned int i;
        unsigned int alg;
        int count;
        vector <int> result;
        vector <long> iterations;
        time_t start;
        time_t finish;
        double timeWithAlgorithm;
        double timeWithoutAlgorithm;

		cout << "Algorithm Timing Started!" << endl;

		cout << "Enter n: ";
		cin >> n;
		vector<int> X(n);
		generate(X.begin(), X.end(), RandNum); //generates the random numbers into the vector; from algorithm library

		cout << "Enter repetitions: ";
		cin >> reps;

		cout << "Enter Algorithm to be timed: ";
		cin >> alg;


		// Phase 1.

		iterations.reserve(reps);

		// Determine the number of iterations of the following while loop that
		// can be executed in one second (it includes the algorithm).

		while (iterations.size() < reps)
		{
			count = 0;
			start = time(0);
			do
			{
				++count;
				// Algorithm that you are timing goes here for this phase
				if (alg == 1)
                    result = prefixAverages1(X, n);
				else
					result = prefixAverages2(X, n);
				//
				finish = time(0);
				// Continue as long as time hasn't changed
			} while (finish == start);
			// Record the number of iterations
			iterations.push_back(count);
		}

		cout << "Iteration counts (with algorithm): " << endl;
		for (i = 0; i < iterations.size(); ++i)
		{
			cout << iterations[i] << " ";
		}
		cout << endl;

		cout << "Sorted iteration counts (with algorithm): " << endl;
		sort(iterations.begin(), iterations.end());
		for (i = 0; i < iterations.size(); ++i)
		{
			cout << iterations[i] << " ";
		}
		cout << endl;

		cout << "Selected value (with algorithm): " << iterations[reps / 2] << endl;
		timeWithAlgorithm = 1000.0 / iterations[reps / 2];
		cout << "Elapsed time (with algorithm): " << timeWithAlgorithm << " ms" << endl;

		iterations.clear();

		// Phase 2.

		iterations.reserve(reps);

		// Now determine the number of iterations of the following while loop that
		// can be executed in one second (it does not include the algorithm).

		while (iterations.size() < reps)
		{
			count = 0;
			start = time(0);
			do
			{
				++count;
				// Algorithm is removed for this phase

				//
				finish = time(0);
				// Continue as long as time hasn't changed
			} while (finish == start);
			// Record the number of iterations
			iterations.push_back(count);
		}

		cout << "Iteration counts (without algorithm): " << endl;
		for (i = 0; i < iterations.size(); ++i)
		{
			cout << iterations[i] << " ";
		}
		cout << endl;

		cout << "Sorted iteration counts (without algorithm): " << endl;
		sort(iterations.begin(), iterations.end());
		for (i = 0; i < iterations.size(); ++i)
		{
			cout << iterations[i] << " ";
		}
		cout << endl;

		cout << "Selected value (without algorithm): " << iterations[reps / 2] << endl;
		timeWithoutAlgorithm = 1000.0 / iterations[reps / 2];
		cout << "Elapsed time (without algorithm): " << timeWithoutAlgorithm << " ms" << endl;

		// Phase 3.

		cout << "Algorithm elapsed time: " << setprecision(20) << timeWithAlgorithm - timeWithoutAlgorithm << " ms" << endl;
		if(alg == 1)
			data << n << "," << setprecision(20) << timeWithAlgorithm - timeWithoutAlgorithm << endl;
		else
			data2 << n << "," << setprecision(20) << timeWithAlgorithm - timeWithoutAlgorithm << endl;
		cout << "Algorithm Timing Ended!" << endl;

		cout << "Time again? Enter Y/N : ";
		cin >> endRun;

	}
	data.close();
    data2.close();
    return 0;
}

vector<int> prefixAverages1(vector<int> X, int n)
{
	int s;
	vector<int> A(n);
	//Let A be an array of n numbers
	for ( int i = 0; i < n-1; i++)
	{
		s = 0;
		for (int j = 0; j < i; j++)
		{
			s = s + X.at(j);
		}
		A[i] = s / (i + 1);
	}
	return A;
}


vector<int> prefixAverages2(vector<int> X, int n)
{
	//Let A be an array of n numbers
	vector<int> A(n);
	int s = 0;
	for (int i = 0; i <= (n - 1); i++)
	{
		s = s + X.at(i);
		A[i] = s / (i + 1);
	}
	return A;
}

