#include "node.h"
bool Node :: is_leaf(){ return left==0 && right==0;}

Node:: Node(char ch, unsigned int freq, Node *left, Node *right)
{
	this->ch=ch;
	this->freq=freq;
	this->left=left;
	this->right=right;
}


