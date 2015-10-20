#ifndef TaySwiftBinaryTree_h
#define TaySwiftBinaryTree_h

#include <iostream>
using namespace std;

class TaySwiftBinaryTree
{
private:
    struct TreeNode {
        char value;
        int count;
        TreeNode* left;
        TreeNode* right;
    };
    TreeNode* root;
public:
    TaySwiftBinaryTree();
    ~TaySwiftBinaryTree();
    
    void Insert(char val);
    TreeNode* Find(char val);
    int CountNodes(TreeNode* tree) const;
    void Print() const;
private:
    void Insert(char val, TreeNode*& tree);
    void Print(TreeNode* tree, int level) const;
};

#endif /* TaySwiftBinaryTree_h */
