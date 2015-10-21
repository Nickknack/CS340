#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "TaySwiftBinaryTree.h"
#include "PriorityQueue.h"

TaySwiftBinaryTree encodingTree;

PCTreeNode HuffmansPrefixCode(PriorityQueue q)
{
	int n = q.GetSize();

	for (int i = 1; i < n - 1; i++)
	{
		PCTreeNode* t1 = new PCTreeNode;
		t1 = &q.DeleteMin();
		PCTreeNode* t2 = new PCTreeNode;
		t2 = &q.DeleteMin();
		PCTreeNode* t = new PCTreeNode;
		t->left = t1;
		t->right = t2;
		t->character = CHAR_MAX;
		t->frequency = t1->frequency + t2->frequency;
		q.Insert(t);
	}
	PCTreeNode toRet = q.DeleteMin();
	return toRet;
}

void TransferEncoding(PCTreeNode* Huffmans, TaySwiftBinaryTree& encodingTree, char code)
{
	if (Huffmans->left != NULL)
	{
		TransferEncoding(Huffmans->left, encodingTree, '0' + code);
	}
	else if (Huffmans->right != NULL)
	{
		TransferEncoding(Huffmans->right, encodingTree, '1' + code);
	}
}

void TransferEncoding(PCTreeNode* Huffmans, TaySwiftBinaryTree& encodingTree)
{
	TransferEncoding(Huffmans, encodingTree, NULL);
}

void Compress(string filename)
{
	ifstream inData;
	inData.open(filename.c_str());
	if (!inData)
	{
		cout << "Error reading file" << endl;
		exit(1);
	}

	// Count occurances of characters in file
	TaySwiftBinaryTree searchTree;
	while (!inData.eof())
	{
		char c;
		inData >> c;
		searchTree.Insert(c);
	}
	inData.close();

	// Transfer the contents of the binary search tree to an array.
	PCTreeNode* tempArr = new PCTreeNode[searchTree.CountNodes()];
	int tempArrSize = searchTree.CountNodes();
	searchTree.ChangeToArray(tempArr);

	// Convert the array into a priority queue by using the BuildHeap algorithm.
	PriorityQueue pq(255);
	pq.BuildFromArray(tempArr, tempArrSize);

	// Generate the optimal prefix code tree using Huffman’s PrefixCode algorithm.
	PCTreeNode Nuffmans = HuffmansPrefixCode(pq);

	// Traverse the prefix code tree and transfer the encoding scheme to the binary search tree.
	// DOESNT FUCKING WORK
	TransferEncoding(&Nuffmans, encodingTree);
	// ===================

	inData.open(filename.c_str());
	if (!inData)
	{
		cout << "Error reading file" << endl;
		exit(1);
	}

	// Open file to compress to
	ofstream outData;
	outData.open((filename + "_compress").c_str());
	if (!inData)
	{
		cout << "Error reading file" << endl;
		exit(2);
	}
	
	// Search through tree for character to encode
	// Write the code to output file.
	while (!inData.eof())
	{
		char c;
		inData >> c;
		outData << encodingTree.Find(c);
	}
	inData.close();
	outData.close();
}

void Decompress(string filename)
{
	// Open compressed file
	ifstream inData;
	inData.open((filename + "_compress").c_str());
	if (!inData)
	{
		cout << "Error reading file" << endl;
		exit(1);
	}
	// Open file to decompress to
	ofstream outData;
	outData.open((filename + "_decompress").c_str());
	if (!inData)
	{
		cout << "Error reading file" << endl;
		exit(2);
	}

	// Loop through each character in file, search if it is a code in the tree
	// If it is, write the character to the decompressed file
	// Otherwise, add the character to a string, and repeat.
	string codeToFind = "";
	while (!inData.eof())
	{
		char c;
		inData >> c;
		codeToFind += c;
		char character = encodingTree.Find(codeToFind);
		if (character != NULL)
		{
			outData << character;
			codeToFind == "";
		}
	}
	inData.close();
	outData.close();
}

int main()
{
    string filename;
    cout << "Enter a filename: ";
    cin >> filename;

	Compress(filename);
	Decompress(filename);

	return 0;
}