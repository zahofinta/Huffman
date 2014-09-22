#include "bitwriter.h"
#include <iostream>

using namespace std;
Bitwriter:: Bitwriter(ofstream& outfile)
{
		this->outfile = &outfile;
		this->buffer  = 0;
		this->size = 0;
		this->writed = 0;
}
void Bitwriter::flush(){
		
		this->buffer = 0;
		this->size = 0;
}
void Bitwriter::writebit(unsigned char bit){		
		buffer = bit ? buffer<<1|1 : buffer<<1|0;
		size++;

		if(size == 8){
				*(this->outfile)<<buffer;
				this->flush();
				//writed++;
				//system("cls");
				//cout<<writed;
		}
}


