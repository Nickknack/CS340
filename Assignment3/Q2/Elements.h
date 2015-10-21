#ifndef Elements_H
#define Elements_H

#include <string>
using namespace std;

struct PCTreeNode {
	char character;
	string code;
	int frequency;
	PCTreeNode* left;
	PCTreeNode* right;
};

#endif /* Elements_H */