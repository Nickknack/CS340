#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// This program determines the run time of an algorithm whose life
// is very short. A measurement technique is used that determines
// the number of times the algorithm can run in one second. The
// elapsed time for one run of the algorithm can then be derived
// from this value.

int main()
{
    double *A;
    double *B;

    unsigned long n;
    unsigned int reps;
    unsigned int i;
    int count;
    vector <long> iterations;
    time_t start;
    time_t finish;
    double timeWithSort;
    double timeWithoutSort;

    cout << "Algorithm Timing Started!" << endl;

    cout << "Enter n: ";
    cin >> n;
  
    cout << "Enter repetitions: ";
    cin >> reps;

    A = new double [n];
    B = new double [n];

// Phase 1.

    srand (time (0));
    for (i = 0; i < n; ++i)
    {
        A[i] = (double) rand ();
    }

    iterations.reserve (reps);

    // Determine the number of iterations of the following while loop that
    // can be executed in one second (it includes the sort algorithm).

    while (iterations.size () < reps)
    {
        count = 0;
        start = time (0);
        do
        {
            ++count;
            copy(A, A + n, B);
	    // Algorithm that you are timing goes here for this phase
            sort(B, B + n);
	    //
	    finish = time (0);
        // Continue as long as time hasn't changed
        } while (finish == start);
        // Record the number of iterations
        iterations.push_back (count);
    }

    cout << "Iteration counts (with sort): " << endl;
    for (i = 0; i < iterations.size (); ++i) 
    {
        cout << iterations [i] << " ";
    }
    cout << endl;

    cout << "Sorted iteration counts (with sort): " << endl;
    sort (iterations.begin (), iterations.end ());
    for (i = 0; i < iterations.size (); ++i) 
    {
        cout << iterations [i] << " ";
    }
    cout << endl;

    cout << "Selected value (with sort): " << iterations [reps / 2] << endl;
    timeWithSort = 1000.0 / iterations [reps / 2];
    cout << "Elapsed time (with sort): " << timeWithSort << " ms" << endl;

    iterations.clear ();

// Phase 2.

    srand (time (0));
    for (i = 0; i < n; ++i)
    {
        A[i] = (double) rand ();
    }

    iterations.reserve (reps);

    // Now determine the number of iterations of the following while loop that
    // can be executed in one second (it does not include the sort algorithm).

    while (iterations.size () < reps)
    {
        count = 0;
        start = time (0);
        do
        {
            ++count;
            copy(A, A + n, B);
	    // Algorithm is removed for this phase
	    //
	    finish = time (0);
        // Continue as long as time hasn't changed
        } while (finish == start);
        // Record the number of iterations
        iterations.push_back (count);
    }

    cout << "Iteration counts (without sort): " << endl;
    for (i = 0; i < iterations.size (); ++i) 
    {
        cout << iterations [i] << " ";
    }
    cout << endl;

    cout << "Sorted iteration counts (without sort): " << endl;
    sort (iterations.begin (), iterations.end ());
    for (i = 0; i < iterations.size (); ++i) 
    {
        cout << iterations [i] << " ";
    }
    cout << endl;

    cout << "Selected value (without sort): " << iterations [reps / 2] << endl;
    timeWithoutSort = 1000.0 / iterations [reps / 2];
    cout << "Elapsed time (without sort): " << timeWithoutSort << " ms" << endl;

// Phase 3.

    cout << "Sort elapsed time: " << timeWithSort - timeWithoutSort << " ms" << endl;

    cout << "Algorithm Timing Ended!" << endl;

    return 0;
}
