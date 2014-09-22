#include "node.h"
#include "includes.cpp"
using namespace std;
typedef std::pair <char,Node*> tree_pairs;


struct comparebykey{
	static bool comparekeys (const tree_pairs & i,const tree_pairs &j)
	{  return i.first<j.first;}


};
struct comparebyvalue{

	static bool comparevalues(const tree_pairs & i,const tree_pairs & j)
	{ return i.second->freq<j.second->freq;}


};


