#ifndef bitwriter_h
# define bitwriter_h
#include <fstream>
using namespace std;
class Bitwriter{
private:
		ofstream* outfile;
		unsigned char buffer;
		int size;
		int writed;
public:
		Bitwriter(ofstream &);
		void flush();
		void writebit(unsigned char bit);
};
#endif