#include "TaySwiftBinaryTree.h"

TaySwiftBinaryTree::TaySwiftBinaryTree()
{
    root = NULL;
}

TaySwiftBinaryTree::~TaySwiftBinaryTree()
{
    
}

void TaySwiftBinaryTree::Insert(char val)
{
    Insert(val, root);
}

void TaySwiftBinaryTree::Insert(char val, TreeNode*& tree)
{
    if (tree == NULL) // Add new node
    {
        tree = new TreeNode;
        tree->value = val;
        tree->count++;
        tree->left = NULL;
        tree->right = NULL;
    }
    else if (val < tree->value) // Node is smaller than root
    {
        Insert(val, tree->left);
    }
    else if (val > tree->value) // Node is greater than root
    {
        Insert(val, tree->right);
    }
    else // Node is the same
    {
        tree->count++;
    }
}

TaySwiftBinaryTree::TreeNode* TaySwiftBinaryTree::Find(char val)
{
    return NULL;
}

int TaySwiftBinaryTree::CountNodes(TreeNode* tree) const
{
    if (tree == NULL)
    {
        return 0;
    }
    else
    {
        return CountNodes(tree->left) + CountNodes(tree->right) + 1;
    }
}

void TaySwiftBinaryTree::Print() const
{
    if (root != NULL)
    {
        cout << endl;
        Print(root, 1);
        cout << endl;
    }
}

void TaySwiftBinaryTree::Print(TreeNode* tree, int level) const
{
    int i;
    if (tree != NULL)
    {
        Print(tree->right, level+1);
        for (i = 0; i < level; i++)
            cout << "\t";
        if ( (tree->left != NULL) && (tree->right != NULL))
            cout << "<";
        else if (tree->right != NULL)
            cout << "/";
        else if (tree->left != NULL)
            cout << "\\";
        cout << endl;
        Print(tree->left, level+1);
    }
}