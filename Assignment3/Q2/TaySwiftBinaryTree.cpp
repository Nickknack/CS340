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
	Insert(val, "", root);
}

void TaySwiftBinaryTree::Insert(char val, string code)
{
	Insert(val, code, root);
}

void TaySwiftBinaryTree::Insert(char val, string code, PCTreeNode*& tree)
{
    if (tree == NULL) // Add new node
    {
        tree = new PCTreeNode;
		tree->character = val;
		tree->frequency = 1;
		tree->code = code;
        tree->left = NULL;
        tree->right = NULL;
    }
    else if (val < tree->character) // Node is smaller than root
    {
		Insert(val, code, tree->left);
    }
	else if (val > tree->character) // Node is greater than root
    {
		Insert(val, code, tree->right);
    }
}

bool TaySwiftBinaryTree::Find(char item, string& code) const
{
	bool found;
	Find(root, item, code, found);
	return found;
}

void TaySwiftBinaryTree::Find(PCTreeNode* tree, char item, string& code, bool& found) const
// Recursively searches tree for item
{
	if (tree == NULL)
		return;
	else if (item < tree->character)
		Find(tree->left, item, code, found);
	else if (item > tree->character)
		Find(tree->right, item, code, found);
	else
	{
        found = true;
		code = tree->code;
	}
}

bool TaySwiftBinaryTree::Find(string item, char& code) const
{
	bool found;
	Find(root, item, code, found);
	return found;
}

void TaySwiftBinaryTree::Find(PCTreeNode* tree, string item, char& code, bool& found) const
// Recursively searches tree for item
{
    cout << item << "\t" << item[0] << endl;
    if (tree == NULL)
        return;
	else if (item[0] == '0')
    {
        Find(tree->left, item.substr(1), code, found);
    }
	else if (item[0] == '1')
    {
        Find(tree->right, item.substr(1), code, found);
    }
    else if (tree->left == NULL && tree->right == NULL)
    {
        found = true;
        code = tree->character;
        return;
    }
}

int TaySwiftBinaryTree::CountNodes() const
{
	return CountNodes(root);
}

int TaySwiftBinaryTree::CountNodes(PCTreeNode* tree) const
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

void TaySwiftBinaryTree::Print(PCTreeNode* tree, int level) const
{
    int i;
    if (tree != NULL)
    {
        Print(tree->right, level+1);
        for (i = 0; i < level; i++)
            cout << "\t";
		cout << " " << tree->character << "(" << tree->code << ")";
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

void TaySwiftBinaryTree::ChangeToArray(PCTreeNode arr[]) const
{
	ChangeToArray(root, arr, 0);
}

int TaySwiftBinaryTree::ChangeToArray(PCTreeNode* tree, PCTreeNode arr[], int i) const
{
	if (tree == NULL)
		return i;

	arr[i].character = tree->character;
	arr[i].frequency = tree->frequency;
	i++;
	if (tree->left != NULL)
		i = ChangeToArray(tree->left, arr, i);
	if (tree->right != NULL)
		i = ChangeToArray(tree->right, arr, i);

	return i;
}