//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: October 30th, 2015
//Last Modified: October 30th, 2015
//Purpose: Functions involved with finding the closest pair amongst a group
//		   of points.
//***************************************************************************

#include "closestPair.h"

using namespace std;

//Constant declerations
const int HIGH_VALUES = 999999;

ClosestPair CallFindClosestPair(ifstream& inFile, int n)
{
	Point* pX;
	Point* pY;

	pX = new Point[n];
	pY = new Point[n];

	ClosestPair clP;
 
 	//Read in the points from the file into the pX array. 
	for (int i = 0; i < n; i++)
	{
		inFile >> pX[i].x;
		inFile >> pX[i].y;
	}

	//Copy the values in pX to pY
	for (int i = 0; i < n; i++)
	{
		pY[i].x = pX[i].x;
		pY[i].y = pX[i].y;
	}

	//Sort pX by the x values with x's that equal being sorted then by y values. 
	InsertionSort(pX, n, 'x');
	//Sort pY by the y values. 
	InsertionSort(pY, n, 'y');

	//Find the closest pair using pX and pY.
	clP = FindClosestPair(pX, pY, n);

	return clP;
}

ClosestPair FindClosestPair(Point* pX, Point* pY, int n)
{
	//Variable Declerations
	ClosestPair clP, clPL, clPR;
	Point* pXL;
	Point* pXR;
	Point* pYL; 
	Point* pYR;
	Point* pYC;

	pXL = new Point[(n / 2)];
	pXR = new Point[(n / 2)];
	pYL = new Point[(n / 2)];
	pYR = new Point[(n / 2)];
	pYC = new Point[n];

	int middle, j, k, x, y;
	float d;

	//if the partion size is 3 or lower there is no longer a reason to keep partioning. It is small enough
	//to just brute force the closest pair in the partion. 
	if (n <= 3)
	{
		clP = BruteForce(pX, n);
	}
	else
	{
		//Calculate what the middle point in the pX partion is and store the point's x and y values
		//in the x and y variables. 
		middle = (n - 1) / 2;
		x = pX[middle].x;
		y = pX[middle].y;

		//put the first half of the values in pX into the pXL partion.
		for (int i = 0; i <= middle; i++)
		{
			pXL[i].x = pX[i].x;
			pXL[i].y = pX[i].y;
		}

		j = 0;

		//Put the  rest of the values in pX into pXR.
		for (int i = middle + 1; i < n; i++)
		{
			pXR[j].x = pX[i].x;
			pXR[j].y = pX[i].y;
			j++;
		}

		//We have sucessfully partitioned the values sorted by x into two new partions (like cutting
		//the graph in half) pXL (The left half of the graph) and pXR (the right half of the graph).

		j = 0;
		k = 0;

		//The pY values need to be partitioned into a left and right value now as well. 
		for (int i = 0; i < n; i++)
		{
			//If the x value of the current point in pY is less than the x value of the
			//middle point in pX OR is equal to the value but has a y value that is
			//less than the middle pX's y value then partition the value into pYL
			//(the left partiton)
			if ((pY[i].x < x) || (pY[i].x == x && pY[i].y <= y && j <= middle))
			{
				pYL[j].x = pY[i].x;
				pYL[j].y = pY[i].y;
				j++;
			}
			//Otherwise the value should be partitioned into pYR (the right side).
			else
			{
				pYR[k].x = pY[i].x;
				pYR[k].y = pY[i].y;
				k++;
			}
		}

		//We recusrivly keep partitioning the new halfs of the graph until we get
		//one that is sufficently small enough to brute force (when it has an n 
		//value of <= 3).
		clPL = FindClosestPair(pXL, pYL, j);
		clPR = FindClosestPair(pXR, pYR, k);

		//clPL and clPR should now contain the closest points for there respective
		//partitions; we then need to find which of these two sets are closer.
		clP = Min(clPL, clPR);

		j = 0;

		//Now we need to check if any of the points that are near the borders of the paritions would be
		//able to make a closer pair than the currently found closest pair. 
		for (int i = 0; i < n; i++)
		{
			if ((pY[i].x >= x - clP.dMin) && (pY[i].x <= x + clP.dMin) && (abs(pY[i].x <= x + clP.dMin)))
			{
				pYC[j].x = pY[i].x;
				pYC[j].y = pY[i].y;
				j++;
			}
		}
		k = j;

		for (int i = 0; i < (k - 1); i++)
		{
			for (int j = (i + 1); j < k; j++)
			{
				if (abs(pYC[j].y - pYC[i].y) > clP.dMin)
				{
					break;
				}

				d = Dist(pYC[i], pYC[j]);

				if (d < clP.dMin)
				{
					clP.dMin = d;
					clP.P1.x = pYC[i].x;
					clP.P1.y = pYC[i].y;
					clP.P2.x = pYC[j].x;
					clP.P2.y = pYC[j].y;
				}

			}
		}
	}

	//Once the border points have been checked, clP will
	//contain the two closest points which we return. 
	return clP;
}

ClosestPair BruteForce(Point* pX, int n)
{
	ClosestPair clP;
	float d;

	//if the amount of points in the partiton is
	//one then just set the minimum distance to
	//some high value
	if (n == 1)
	{
		clP.dMin = HIGH_VALUES;
	}
	//otherwise bruteForce the closestPair
	else
	{
		//Check the distance between the first
		//point and the second point; this, for now
		//these points are the shortest points
		//Set clP accordingly. 

		d = Dist(pX[0], pX[1]);

		clP.dMin = d;

		clP.P1.x = pX[0].x;
		clP.P1.y = pX[0].y;
		clP.P2.x = pX[1].x;
		clP.P2.y = pX[1].y;

		//If the partition has exactly three points...

		if (n == 3)
		{
			//find the distance between the first point (0)
			//and the third point (2).
			//If there distance is less than that of the current
			//closest pair then we have a new closest pair.
			d = Dist(pX[0], pX[2]);

			if (d < clP.dMin)
			{
				clP.dMin = d;
				clP.P2.x = pX[2].x;
				clP.P2.y = pX[2].y;
			}

			//find the distance between the second point (1)
			//and the third point (2).
			//If there distance is less than that of the current
			//closest pair then we have a new closest pair.
			d = Dist(pX[1], pX[2]);

			if (d < clP.dMin)
			{
				clP.dMin = d;

				clP.P1.x = pX [1].x;
            	clP.P1.y = pX [1].y;
            	clP.P2.x = pX [2].x;
            	clP.P2.y = pX [2].y;
			}
		}
	}

	return clP;
}

ClosestPair Min(ClosestPair& clPL, ClosestPair& clPR)
{
	ClosestPair clP;

	//Find the closer pairs between two ClosestPairs. 
	if (clPL.dMin < clPR.dMin)
	{
		clP.dMin = clPL.dMin;
    	clP.P1.x = clPL.P1.x;
    	clP.P1.y = clPL.P1.y;
    	clP.P2.x = clPL.P2.x;
    	clP.P2.y = clPL.P2.y;
	}
	else
	{
		clP.dMin = clPR.dMin;
    	clP.P1.x = clPR.P1.x;
   		clP.P1.y = clPR.P1.y;
    	clP.P2.x = clPR.P2.x;
    	clP.P2.y = clPR.P2.y;
	}

	return clP;
}

float Dist (Point& p1, Point& p2)
{
	//Calculates the distance between two points. (square root of((x1 - x2)^2 + (y1 - y2)^2)))
	float dX, dY;

	dX = pow((p1.x - p2.x), 2);
	dY = pow((p1.y - p2.y), 2);

	return(sqrt(dX + dY));
}

void InsertionSort(Point* p, int n, char valueToSort)
{
	//An instertion sort that sorts a Point array either by x values or y values
	//if it is sorting by x values it will also sort it by y values when the x's are equal
	Point temp;
	int j;

	for (int i = 0; i < n; i++)
	{
		temp.x = p[i].x;
		temp.y = p[i].y;
		j = i;

		if (valueToSort == 'x')
		{
			while (j > 0 && ((temp.x < p[j - 1].x) || ((temp.x == p[j - 1].x) && (temp.y < p[j - 1].y))))
			{
				p[j].x = p[j - 1].x;
				p[j].y = p[j - 1].y;
				j--;
			}
		}
		else
		{
			while (j > 0 && (temp.y < p[j - 1].y))
			{
				p[j].x = p[j - 1].x;
				p[j].y = p[j - 1].y;
				j--;
			}
		}

		p[j].x = temp.x;
		p[j].y = temp.y;
	}
}