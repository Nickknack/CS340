/*
  This source file is adapted from feigen.c that comes with the book
  Numeric Algorithm with C by Frank Uhlig et al. I cannot find the
  license of the original source codes. I release my modifications under
  the MIT license. The modified version requires C99 as it uses complex
  numbers. I may modify the code if this is a concern.
*/

/* The MIT License

   Copyright (c) 1996 Frank Uhlig et al.
                 2009 Genome Research Ltd (GRL).

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

/* ------------------------- MODULE feigen.c ------------------------ */

#include <math.h>
#include <float.h> /* for DBL_EPSILON */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <complex.h>
#include <fstream>

using namespace std;

#define N 15

int n_eigeng(double *_a, int n, double *evalr, double *evali, double *_evec);

/* -------------------------- END feigen.c -------------------------- */

int main(void)
{

  //******Modified for assignment*****
  double a[N][N];
  ifstream inputMatrix;

  inputMatrix.open("transitionMatrix.txt");

  if (!(inputMatrix))
  {
    cout << endl << endl << "ERROR: FILE UNABLE TO OPEN" << endl << endl;
    return 1;
  }

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      inputMatrix >> a[i][j];
    }
  }
  //******Modified for assignment*****



	/*static double   a[N][N] = {{0.0, 0.0, 1.0, 0.5},
				   {0.33, 0.0, 0.0, 0.0},
				   {0.33, 0.5, 0.0, 0.5},
				   {0.33, 0.5, 0.0, 0.0}};*/
	double *mem, *evalr, *evali, *evec;
	int i;
	mem = (double*)calloc(N * N + N * 2, sizeof(double));
	evec = mem;
	evalr = evec + N * N;
	evali = evalr + N;
	n_eigeng(a[0], N, evalr, evali, evec);
	for (i = 0; i <= N - 1; i++) {
		printf("%12.6e ", evec[i * N]);
		printf("\n");
	}
	printf("\n");

	free(mem);
	return 0;
}
