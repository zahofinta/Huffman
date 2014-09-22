#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H
#include "includes.cpp"
typedef std::pair <char,Node*> tree_pairs;

#define buf_size 1024
using namespace std;
void frequency_for_char(ifstream&, map<char, unsigned int>&);
void print_frequency(map<char, unsigned int>&);
void print_code(map<char, string>&);
void searchdir(char*);
vector<tree_pairs>* set_nodes_in_vector_by_map(map<char, unsigned int>&);
void  sort_pairs(vector<tree_pairs> &);
Node* root(vector<tree_pairs>&);
void newalphabet(Node*, string, map<char, string>&);
int bitstring(string, map<char, string>&, ofstream&);
string get_content_of_file(ifstream&);
string get_content_of_file(string);
void write_array_content_to_file(vector<pair<char, unsigned int>*>& result);
map <char, unsigned int> frequency_map(ifstream& in);
void write_map_to_file(map <char, unsigned int> & freqmap,char *filename);
int count_nodes(Node*);
int count_leaves(Node*);
string map_to_bit_string(map<char, unsigned int> m);
void bitstring(string toencode, ofstream& writer);
unsigned int read32bit_integer(ifstream& reader);
char read8bit_char(ifstream& reader);
map<char, unsigned int> read_map_from_file(ifstream& reader);
//string to_bits(string data, short not_read);
string decode (Node *r, string& bits);
void write_decoded_information(Node* R,string decodestring, ofstream& test);
void delete_tree(Node*);
map <char,string> encode_table(Node* root);
#endif