#include "includes.cpp"
#include "help_functions.h"
typedef std::pair <char,Node*> tree_pairs;
#include "Compares.cpp"
using namespace std;
//za  debuga
int count_nodes(Node *root)
{
		if (root==NULL)
				return 0;
		else if(root->is_leaf())
				return 1;
		else return count_nodes(root->left)+count_nodes(root->right)+1;

}
//za debuga
int count_leaves(Node *root)
{ int count =0; 
if (root->is_leaf())
		count++;
else {
		if(root->left!=NULL)
				count+=count_leaves(root->left);
		if (root->right!=NULL)
				count+=count_leaves(root->right);
}

return count;

}

//po daden fail vrushta sudurajnieto mu
string get_content_of_file(string filename){
		ifstream reader;
		reader.open(filename.data(), ios::in | ios::binary);
		stringstream builder;
		while(!reader.eof()){
				unsigned char help_char=reader.get();
				builder<<help_char;			
		}
		builder<<"\0";
		string result = builder.str();
		reader.close();
		return result;
}
string get_content_of_file(ifstream& reader){
		
		stringstream builder;
		while(!reader.eof()){
				unsigned char help_char=reader.get();
				builder<<help_char;					
		}	
		builder<<"\0";
		string result = builder.str();	
		reader.close();
		return result;
}
//namira chestotite na vseki simvol po daden vhoden fail i map
void frequency_for_char(ifstream &in, map<char, unsigned int> & freq)
{

		if(!in)
		{
				cout << "could not open for reading" << endl;
		}
		char buffer[buf_size];
		while( !in.eof())
		{   
				in.read(buffer,buf_size);
				for(int i=0;i<in.gcount();i++)
				{ 
						freq[buffer[i]]++;
				}

		}
		in.close();
}
// vrushta map s chestotite na simvolite 
map <char, unsigned int> frequency_map(ifstream& in)
{ 
		map <char, unsigned int> freqmap;
		if (!in)
		{
				cout << "could not open for reading " << endl;
		}
		char buffer[buf_size];
		while(!in.eof())
		{
				in.read(buffer,buf_size);
				for (int i=0;i<in.gcount();i++)
				{
						freqmap[buffer[i]]++;
				}
				return freqmap;
		}
}
//izkarva na ekrana chestotite na simvolite
void print_frequency(map<char, unsigned int> &freq){
		map<char, unsigned int>::const_iterator it;
		int chars = 0;
		for(it = freq.begin(); it!=freq.end(); it++)
		{
				chars+=it->second;
				cout<< it->first << " - " << it->second << endl;
		}
		cout<<chars<<" "<<chars*sizeof(char)<<endl;
}
//izkarva novata azbuka s bitove
void print_code(map<char, string> &codemap){
		map<char,string>::const_iterator it;
		for(it = codemap.begin(); it!=codemap.end(); it++){
				cout<< it->first << " - " << it->second << it->second.size() << endl;
		}
}
//pulni vectora s dvoiki i go vrushta
vector <tree_pairs>* set_nodes_in_vector_by_map(map <char, unsigned int>  &freq)
{  
		map <char, unsigned int>::const_iterator it;
		vector <tree_pairs> *pairs_by_chars_and_nodes=new vector <tree_pairs>(); 
		for (it=freq.begin();it!=freq.end();++it)
		{ 
				pairs_by_chars_and_nodes->push_back(make_pair(it->first,new Node(it->first,it->second,NULL,NULL)));

		}
		return pairs_by_chars_and_nodes;
}
//sortira vectora ot dvoiki po vtori element
void  sort_pairs(vector<tree_pairs> & pairs)
{
		sort(pairs.begin(),pairs.end(), comparebyvalue::comparevalues);
}
//stroi darvoto i vrushta chestotata na korena
Node* root (vector <tree_pairs> & pairs)
{ 
		while (pairs.size()>1)
		{
				Node* a=pairs[0].second;
				Node* b =pairs[1].second;
				Node* mixab=new Node(char(0),a->freq+b->freq,a,b);
				pairs.erase(pairs.begin());
				pairs.erase(pairs.begin());
				pairs.push_back(make_pair(char(0),mixab));
				sort_pairs(pairs);
		}
		return pairs[0].second;
}
// stroi azbukata s bitove
void newalphabet(Node *root,string code,map <char,string> & code_map)
{
		if(root->is_leaf())
		{  
				code_map[root->ch]=code;
		}
		if (root->left!=NULL)
		{
				newalphabet(root->left,code+ char(0),code_map);
		}
		if(root->right!=NULL)
		{  
				newalphabet(root->right,code+char(1),code_map);
		}

}
//chete 32bitovo pololijelno chislo 
unsigned int read32bit_integer(ifstream& reader){

		char bytes[4];
		for(int i = 0; i<4; i++){
				bytes[i] = reader.get();
		}
		unsigned int result = 0;
		for(int i = 0; i<4; i++){
				result = (result << 8) | ((unsigned char) bytes[i]);
		}

		//cout<<result<<endl;
		return result;
}
//chete char
char read8bit_char(ifstream& reader){
		char to_read;
		to_read = reader.get();
		return to_read;
}
//prochita mapa po daden fail kato se mesti poziciqta na kursora 
map<char, unsigned int> read_map_from_file(ifstream& reader){
		map<char, unsigned int> to_return;
		unsigned int map_entries_count = read32bit_integer(reader);
		for(int i = 0; i<map_entries_count; i++){
				reader.seekg(4*i+4+i);
				char char_to_put = read8bit_char(reader);
				reader.seekg(4*i+5+i);
				//cout<<char_to_put<<" -> ";
				unsigned int int_to_put = read32bit_integer(reader);
				to_return[char_to_put]=int_to_put;
		}
		return to_return;
}
//prevrushta mapa na string ot bitove
string map_to_bit_string(map<char, unsigned int> m){
		unsigned int size = m.size();
		string result = "";
		unsigned char g=1;
		int br=0;
		bitset<32> map_entries;
		//kolko zapisa ima v mapa
		while(br<32)
		{
				map_entries[br]=(size&g);
				size=size>>1;
				br++;
		}
		result+=map_entries.to_string();
		map<char, unsigned int> :: iterator it; 
		bitset <8> bit_value;
		for(it = m.begin(); it!=m.end(); it++){
				char map_char = it->first;
				for (int i=0;i<8;i++)
				{
						bit_value[i] = map_char & 1;
						map_char = map_char>>1;
				}
				result = result+bit_value.to_string();
				unsigned int sec = it->second;
				int br1=0;
				bitset <32> current_entry;
				while(br1<32)
				{
						current_entry[br1] = (sec&g);
						sec=sec>>1;
						br1++;
				}
				result+=current_entry.to_string();
		}
		return result;
}

/*string to_bits(string data, short not_read){
		string to_return = "";
		const char* array_of_chars = data.data();
		int array_len = data.size();
		for(int i = 0; i<array_len-1; i++){
				int bits = 0;
				if(i == array_len-2){
						bits = not_read;
				}
				while(bits<8){
						char current_char = array_of_chars[i];
						current_char = current_char >> (8 - bits - 1);
						current_char = current_char & char(1);
						to_return += current_char;
						bits++;
				}
		}
		return to_return;
}*/
// (vrushta decodiraniq string) / za debuga (proverka na stringa dali e parvonachalniq)
string decode (Node *r, string& bits){
	
	unsigned	int bits_len = bits.size();
		string to_return = "";
		stringstream buffer;
		for(unsigned int i = 0; i<bits_len; i++){				
				Node *k = r;		
				while(!k->is_leaf()&&i<bits_len ){
						if(bits[i] == char(1)){
								k = k->right;
						}
						else{
								k = k->left;
						}
						i++;
				}
				buffer << k->ch;

				i--;
		}
		to_return=buffer.str();
		return to_return;
}
map <char,string> encode_table (Node* root){
		map<char,string> encoding_table;
		newalphabet(root,"",encoding_table);
		return encoding_table;
}


//zapisva bitovete po v fail po daden fail ,map i fail v koito da se zapishat
int bitstring(string toencode, map <char, string>& alphabet, ofstream& writer){
		Bitwriter *btw = new Bitwriter(writer);
		int bit_0 = 0;
		
		for(int i=0;i<toencode.size();i++){
				
				string k = alphabet[toencode[i]];
				if(i == toencode.size()-1){
						while(k.size()%8!=0){
								k+=char(0);
								bit_0++;
						}
						}
				
				for(int j = 0; j<k.size(); j++){
						btw->writebit(k[j]);				
				}
}
		
		delete btw;
		return bit_0;
}
//zapisva informaciqta ,koqto se e dekodirala
void write_decoded_information(Node* R,string decodestring, ofstream& test){
		string bits = "";
		cout<<decodestring.size();
		stringstream buffer;

		for(int i = 0; i<decodestring.size(); i++){
				unsigned char c = decodestring[i];

				for(int j = 0; j<8; j++){
						if((c&128) == 0){
								buffer<<char(0);
								
						}
						else{


								buffer<<char(1);}
						c = c<<1;

				}
				
		}
	
		buffer<<"\0";
		bits = buffer.str();
		string k = decode(R, bits);
		test.write(k.data(), k.size());
}


void bitstring(string toencode, ofstream& writer){
		Bitwriter *btw = new Bitwriter(writer);
		for(int i=0; i<toencode.size(); i++){
				char to_write = toencode[i] == '0' ? char(0) : char(1);
				btw->writebit(to_write);
		}
		delete btw;
}


//za debuga
void make_pair_vector_from_tree(Node *root,vector<pair<char, unsigned int>*>& result,int i)
{
		if (root==NULL)  return;
		if(root!=NULL)
		{  
				if(i>=result.size()){
						int len = result.size();
						while(len<=i){
								result.push_back(NULL);
								len++;
						}
				}
				result.at(i)=new pair<char, unsigned int>(root->ch,root->freq);
		}

		make_pair_vector_from_tree(root->left,result,2*i+1);
		make_pair_vector_from_tree(root->right,result,2*i+2);		

}
//za debuga
void write_array_content_to_file(vector<pair<char, unsigned int>*>& result)
{  
		ofstream fout("teest.txt");
		for(int i = 0; i<result.size(); i++){
				if (result[i]!=0){
						fout <<i<<" "<< result[i]->first << " " << result[i]->second << endl;
				}
		}
}
void delete_tree(Node * root)
{
		if(root==NULL){
				return;
		}
		else{
				delete_tree(root->left);
				delete_tree(root->right);
				delete root;
		}


}


////po daden put namira vsichki direktorii
/*void searchdir (char *argv)
{
		WIN32_FIND_DATAA FindFileData;
		HANDLE hFind;
		char sizedir[MAX_PATH];

		strncpy(sizedir, argv, MAX_PATH);
		strncat(sizedir, "\\*", MAX_PATH);

		_tprintf (TEXT("Target file is %s\n"), argv);
		hFind = FindFirstFile(sizedir, &FindFileData);
		cout<<"files are: \n";

		while (FindNextFile(hFind, &FindFileData)!=0) 
		{ 
				int size_filename=strlen(FindFileData.cFileName);
				char* filename = new char[size_filename+1];
				strncpy(filename, FindFileData.cFileName,size_filename);
				cout << filename << " ";
				if(FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY && strcmp(filename, "..")!=0 && strcmp(filename,".")!=0){
						cout << " <DIR> ";
						char help[MAX_PATH];
						strncpy(help, "\\", MAX_PATH);
						strncat(help, FindFileData.cFileName, MAX_PATH);
						char innerdir[MAX_PATH];
						strncpy(innerdir,argv,MAX_PATH);
						strncat(innerdir,help,MAX_PATH);
						cout << innerdir <<endl;
						searchdir(innerdir);

				}

				cout <<endl;
				delete []filename;
		} 

		FindClose(hFind);

}*/

