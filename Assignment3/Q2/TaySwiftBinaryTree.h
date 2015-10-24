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
	void Insert(char val, string code);
	bool Find(char item, string& code) const;
	bool Find(string item, char& code) const;
    int CountNodes() const;
    void Print() const;
	void ChangeToArray(PCTreeNode arr[]) const;
private:
	int CountNodes(PCTreeNode* tree) const;
	void Insert(char val, string code, PCTreeNode*& tree);
	void Print(PCTreeNode* tree, int level) const;
	int ChangeToArray(PCTreeNode* tree, PCTreeNode arr[], int i) const;
	void Find(PCTreeNode* tree, char item, string& code, bool& found) const;
	void Find(PCTreeNode* tree, string item, char& code, bool& found) const;
};

#endif /* TaySwiftBinaryTree_h */
