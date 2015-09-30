//***************************************************************************
//Names: Nicholas Kowalchuk, Brayden Streibel, Evan Boyle
//Created: September 12th, 2015
//Last Modified: September 14th, 2015
//Purpose: Functions for creating and working with a binary search tree.
//***************************************************************************
#include "BinarySearchTree.h"

using namespace std;

int Initialize(BSTNode*& tree)
{
	tree = NULL;
	return BST_INITIALIZED;
}

int Insert(const int value, BSTNode*& tree)
{
	int result;

	//If the tree is NULL then it doesn't have any nodes, therefore set values of 
	//first node.
	if (tree == NULL)
	{
		tree = new BSTNode;
		tree->value = value;
		tree->left = NULL;
		tree->right = NULL;
		result = OK;
	}
	else
	{
		//If the value of the node to insert is less than the current node's value 
		//then insert it to the left of the current node.
		if (value < tree->value) 
		{
			result = Insert(value, tree->left);
		}	
		//Else if the value is greater then insert the new node to the right of the 
		//current node.
		else if (value > tree->value)
		{
			result = Insert(value, tree->right);
		}
		//Otherwise the values are equal, the node is a duplicate.
		else
		{
			result = DUPLICATE;
		}
	}

	return result;
}

void RemoveTreePostOrder (BSTNode*& tree)
{
	if (tree == NULL)
	{
		return; 
	}
	RemoveTreePostOrder(tree->left);
	RemoveTreePostOrder(tree->right);
	//if, or once, the node has no more children, delete the node. 
	delete tree; 
	return;
}

void AverageDepth(BSTNode*& tree, int currentDepth, float& totalDepth, int& nodeCount)
{

	if (tree == NULL) 
	{
		//If the current node is NULL, then we have surpassed the tree; therefore the depth 
		//is the current depth -1 (-1 because we have gone 1 node past the last node)
		return;
	}
	totalDepth = totalDepth + currentDepth;
	nodeCount++;
	AverageDepth(tree->left, currentDepth + 1, totalDepth, nodeCount);
	AverageDepth(tree->right, currentDepth + 1, totalDepth, nodeCount);
	return;
}

float AverageDepthOfMTreesNNodes(int nodes, int trees)
{
	BSTNode* tree;
	int result; //Used to catch the error checking returns of certain functions.
	float totalAverageDepth = 0;
	float treeAverageDepth;
	int nodeCount;

	int randValue;

	//Generate trees equal to the amount of trees variable with nodes amount of
	//nodes and calculate the average depth of the trees. 
	for (int i = 0; i < trees; i++)
	{
		treeAverageDepth = 0;
		nodeCount = 0;
		//initialize tree.
		result = Initialize(tree); 

		for (int j = 0; j < nodes; j++)
		{
			randValue = rand();
			//Generate the nodes and insert them into the tree
			Insert(randValue, tree);
		}
		//Get the average depth of the tree
		AverageDepth(tree, 0, treeAverageDepth, nodeCount);
		treeAverageDepth = float(treeAverageDepth) / float(nodeCount);

		//Add the average depth of the tree to the running total depth.
		totalAverageDepth = totalAverageDepth + treeAverageDepth;

		//done with tree; delete it and generate a new one.
		RemoveTreePostOrder(tree);
	}

	//return the average of all the tree depths.
	return (totalAverageDepth / trees);
}