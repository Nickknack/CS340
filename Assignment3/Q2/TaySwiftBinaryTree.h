#ifndef TaySwiftBinaryTree_h
#define TaySwiftBinaryTree_h

#include <iostream>
using namespace std;
#include "Elements.h"

class TaySwiftBinaryTree
{
private:
    PCTreeNode* root;
public:
    TaySwiftBinaryTree();
    ~TaySwiftBinaryTree();
    
    void Insert(char val);
	void Insert(char val, int code);
	int Find(char item) const;
	char Find(int item) const;
    int CountNodes() const;
    void Print() const;
	void ChangeToArray(PCTreeNode arr[]) const;
private:
	int CountNodes(PCTreeNode* tree) const;
	void Insert(char val, int code, PCTreeNode*& tree);
	void Print(PCTreeNode* tree, int level) const;
	int ChangeToArray(PCTreeNode* tree, PCTreeNode arr[], int i) const;
	void Find(PCTreeNode* tree, char item, int& found) const;
	void Find(PCTreeNode* tree, int item, char& found) const;
};

#endif /* TaySwiftBinaryTree_h */
