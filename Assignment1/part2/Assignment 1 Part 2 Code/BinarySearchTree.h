//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibal, Evan Boyle
//Created: September 12th, 2015
//Last Modified: September 14th, 2015
//Purpose: Functions for creating and working with a binary search tree.
//***************************************************************************
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <cstdlib>
#include <iostream>

//Constant integer values for error checking
const int BST_INITIALIZED = -11;
const int OK = -12;
const int DUPLICATE = -13;
const int NOT_FOUND = -14;

//The maximum value for the random value generated
//const int RANDOM_MAX = 5000;

//The binary search tree is made up of nodes (BSTNode)
struct BSTNode
{
	int value;
	BSTNode* left;
	BSTNode* right;
};

int Initialize(BSTNode*& tree);
	//purpose: Initialize the binary search tree, setting it to NULL.
	//Parameter(s): A BSTNode called tree which is the tree that is being initialized.
	//Precondition(s): N/A
	//Return: an integer which returns a constant depending on what happens
	//Side Effect: The node passed in will be initialized.

int Insert (const int value, BSTNode*& tree);
	//purpose: Inserts a node into the proper position in the tree.
	//Parameter(s): a integer value that will be the element of the new Node and a 
	//	pointer to a BSTNode called tree which is the tree that the node will beinserted to.
	//Precondition(s): The tree has already been initialized
	//Return: an integer which returns a constant depending on what happens
	//Side Effect: a Node will be added to the tree in the appropriate position.

void RemoveTreePostOrder(BSTNode*& tree);
	//purpose: Delete the tree by traversing in Post Order and deleting the nodes. 
	//Parameter(s): A pointer to a BSTNode called tree which is the tree that the node 
    //				will beinserted to.
	//Precondition(s): The tree has already been initialized
	//Return: N/A
	//Side Effect: the tree (all of the nodes) will be deleted. 

void AverageDepth(BSTNode*& tree, int currentDepth, int& totalDepth, int& nodeCount);
	//purpose: Gets the average depth of the nodes in the tree.
	//Parameter(s):  a pointer to a BSTNode called tree, the current nodes depth called
	//				 currentDepth, the running total depth caleld totalDepth, and
	//				 the running total of nodes called nodeCount.
	//Precondition(s): The tree has already been initialized.
	//Return: N/A
	//Side Effect: totalDepth will now contain the sum of the depths of all of the trees
	//             nodes. nodeCount will now contain the amount of nodes in the tree

float AverageDepthOfMTreesNNodes(int nodes, int trees);
	//purpose: Generates M trees with N Nodes and calculates the average depth.
	//Parameter(s): nodes (n) which is the amount of nodes in each tree 
    //              and trees (m) which is the amount of trees with n nodes to generate.
	//Precondition(s): N/A
	//Return: an integer which is the average depth of m trees with n nodes.
	//Side Effect: N/A

#endif