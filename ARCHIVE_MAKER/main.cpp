#include "help_functions.h"
#include "includes.cpp"
typedef std::pair <char,Node*> tree_pairs;
int main (int argc, char* argv[])
{   
		if(argc != 4){
				printf("The number of arguments isn't correct!\n");
		}
		else{
				char* command = argv[1];
				if(strcmp(command, "compress")==0){
						string dir = argv[2];
						string to_put = argv[3];
						string temp_file = "temp.dir";
						ArchiveDirectoryTree(dir, temp_file);
						map<char, unsigned int> freq;//chastoten map
						//map <char, string> codemap;//map kudeto vseki char e napraven na string ot bitove
						ofstream writer(to_put, ios::binary|ios::app);//obekt za zapisvane na gotoviq fail
						ifstream reader(temp_file, ios::binary);//chetec na faila s direktoriite
						frequency_for_char(reader, freq);
						//print_frequency(freq);
						//chete faila s direktoriite i suzdava map s chestoti
						string map_bits_string = map_to_bit_string(freq);
						//cout << map_bits_string << endl;//string ot bitove za chestotite
						bitstring(map_bits_string, writer);//zapisva stringa ot bitove vuv fail
						//vektor s naredeni dvoiki
						vector <tree_pairs> *pair_vector = set_nodes_in_vector_by_map(freq);
						sort_pairs(*pair_vector);//sortirane na vectora
						Node* huffman_tree_root = root(*pair_vector);//suzdava durvoto na huffman
						map <char, string> codemap=encode_table(huffman_tree_root);//map kudeto vseki char e napraven na string ot bitove						
						//print_code(codemap);
						string file_content = get_content_of_file(temp_file);				
						bitstring(file_content, codemap, writer);
						//delete_tree(huffman_tree_root);
						writer.close();
						reader.close();
						remove("temp.dir");
				}
				else if(strcmp(command, "extract")==0){
						string to_extract = argv[2];
						string dir = argv[3];
						string temp = "temp.tmp";
						ofstream writer(temp, ios::binary|ios::app);
						ifstream reader(to_extract, ios::binary);				
						map <char, unsigned int> decode_freq;
						decode_freq = read_map_from_file(reader);
						vector<tree_pairs>* decode_pair_vector = set_nodes_in_vector_by_map(decode_freq);
						sort_pairs(*decode_pair_vector);
						Node * huffman_tree_root = root(*decode_pair_vector);
						string decode_string = get_content_of_file(reader);
						write_decoded_information(huffman_tree_root, decode_string, writer);
						//delete_tree(huffman_tree_root);
						reader.close();
						writer.close();
						ExtractDirectoryTree(dir, temp);	
						remove("temp.tmp");
				}
				else{
						printf("Not valid command!\n");
				}
		}
		
}