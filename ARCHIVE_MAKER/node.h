#ifndef node_h
#define node_h

struct Node
{
char ch;
 unsigned int freq;
 Node *left;
 Node *right;
 bool is_leaf();
 

 Node(char ch, unsigned int freq, Node *left, Node *right);
 
};
#endif