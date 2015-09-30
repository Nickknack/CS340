//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: September 12th, 2015
//Last Modified: September 14th, 2015
//Purpose: Topological sort functions
//***************************************************************************

#ifndef TOPOLOGICAL_H
#define TOPOLOGICAL_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Leader;
struct Follower;

struct Follower
{
	Leader* adjacentLeader;
	Follower* nextFollower;
};

struct Leader
{
	string element;
	int inDegree;
	Leader* nextLeader;
	Follower* firstFollower;
};

void TopologicalSort(ifstream& input);

Leader* BuildList (string w, Leader* head, Leader*& tail, int& i);

#endif